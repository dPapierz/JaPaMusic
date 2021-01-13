#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string.h>
#include <future>

#include <boost/asio.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <sndfile.hh>
#include <portaudio.h>

#include "../Utility/Structs.h"
#include "../Networking/Client.h"

#include "../Networking/Messages/MessageTrackRequest.h"
#include "../Networking/Messages/MessageTrackResponse.h"

#include "../Networking/Messages/MessageDataRequest.h"
#include "../Networking/Messages/MessageDataResponse.h"

#include "../Networking/Messages/MessageFilesRequest.h"
#include "../Networking/Messages/MessageFilesResponse.h"

namespace JaPaMusic {

	const int MUSIC_BUFFER_FRAMES(100);

	class Player {

		public:
			Player(boost::asio::io_context &io_context, std::string host, std::string service);
			~Player();

			std::vector<std::string> getAvailableTracks();
			void getTrackInfo(const std::string trackName);

			void start();
			void end();
			
			void play();

			static TrackInfo getInfo(std::string track) {
				SF_INFO info;
				SNDFILE *file;
				TrackInfo trackInfo;

				file = sf_open(track.c_str(), SFM_READ, &info);
				trackInfo.filename = track;
				trackInfo.currentFrame = 0;
				trackInfo.frames = info.frames;
				trackInfo.samplerate = info.samplerate;
				trackInfo.channels = info.channels;
				trackInfo.format = info.channels;
				trackInfo.sections = info.sections;
				trackInfo.seekable = info.seekable;
				sf_close(file);

				return trackInfo;
			}

			static void getMusicData(std::string filename, int frame, float *buffer, int bufferSize) {
				SF_INFO info;
				SNDFILE *file  = sf_open(filename.c_str(), SFM_READ, &info);

				sf_count_t a = sf_seek(file, frame, SF_SEEK_CUR);
				sf_count_t b = sf_read_float(file, buffer, bufferSize);

				sf_close(file);
			}

			inline TrackInfo getInfo() {
				return info_;
			}
			
		private:
			boost::asio::io_context &io_context_;
			std::string host_;
			std::string service_;

			std::vector<float> buffer_;

			PaStream *stream_;
			PaError error_;
			TrackInfo info_;
	};

}

#endif // PLAYER_H
