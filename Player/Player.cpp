#include "Player.h"

namespace JaPaMusic {

	Player::Player(boost::asio::io_context &io_context, std::string host, std::string service) :
		io_context_(io_context),
		host_(host),
		service_(service) {
		error_ = Pa_Initialize();
		if (error_ != paNoError) {
			fprintf(stderr, "Problem initializing\n");
		}
	}

	Player::~Player() {
		/*  Shut down portaudio */
		error_ = Pa_CloseStream(stream_);
		if (error_ != paNoError) {
			fprintf(stderr, "Problem closing stream\n");
			return;
		}

		error_ = Pa_Terminate();
		if (error_ != paNoError) {
			fprintf(stderr, "Problem terminating\n");
		}
	}


	std::vector<std::string> Player::getAvailableTracks() {
		MessageFilesRequest request;
		MessageFilesResponse *response;

		boost::asio::io_context io_context;
		Client client(io_context, host_, service_);
		client.write(&request);
		response = (MessageFilesResponse *) client.read();
		
		return response->getData();
	}

	void Player::getTrackInfo(const std::string trackName) {
		MessageTrackRequest request;
		MessageTrackResponse *response;

		request.setData(trackName);

		boost::asio::io_context io_context;
		Client client(io_context, host_, service_);
		client.write(&request);
		response = (MessageTrackResponse *) client.read();
		info_ = response->getData();

		buffer_.resize(MUSIC_BUFFER_FRAMES * info_.channels);

		error_ = Pa_OpenDefaultStream(&stream_
		                              ,0                     /* no input */
		                              ,info_.channels         /* stereo out */
		                              ,paFloat32             /* floating point */
		                              ,info_.samplerate
		                              ,MUSIC_BUFFER_FRAMES
		                              ,NULL
		                              ,NULL);
		if (error_ != paNoError) {
			fprintf(stderr, "Problem opening Default Stream\n");
			return;
		}
	}

	void Player::start() {
		/* Start the stream */
		error_ = Pa_StartStream(stream_);
		if (error_ != paNoError)
			fprintf(stderr, "Problem opening starting Stream\n");
	}

	void Player::play() {
		MessageDataRequest request;
		MessageDataResponse *response;

		request.setData(info_);

		boost::asio::io_context io_context;
		Client client(io_context, host_, service_);
		client.write(&request);
		response = (MessageDataResponse *) client.read();
		buffer_ = response->getData();


		error_ = Pa_WriteStream(stream_, buffer_.data(), MUSIC_BUFFER_FRAMES);
		if (error_ != paNoError) {
			fprintf(stderr, "Problem writing to Default Stream\n");
		}

		info_.currentFrame += MUSIC_BUFFER_FRAMES;
	}

	void Player::end() {
		error_ = Pa_StopStream(stream_);
		if (error_ != paNoError)
			fprintf(stderr, "Problem closing starting Stream\n");
	}
}






