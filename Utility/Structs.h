#ifndef STRUCTS_H
#define STRUCTS_H

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <sndfile.hh>

namespace JaPaMusic {

	struct TrackInfo {
			std::string filename = "";
			float currentFrame = 0;
			int frames = 0;
			int samplerate = 0;
			int channels = 0;
			int format = 0;
			int sections = 0;
			int seekable = 0;

		private:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version) {
				ar &filename;
				ar &currentFrame;
				ar &frames;
				ar &samplerate;
				ar &channels;
				ar &format;
				ar &sections;
				ar &seekable;
			}
	};

}

#endif // PLAYER_H
