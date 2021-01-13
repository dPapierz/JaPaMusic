#include "Server.h"

namespace JaPaMusic {

	Server::Server(boost::asio::io_context &io_context, unsigned short port) :
		io_context_(io_context),
		acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {

		pointer new_conn(new Connection(io_context));
		acceptor_.async_accept(new_conn->socket(),
		                       boost::bind(&Server::handle_accept, this,
		                                   boost::asio::placeholders::error, new_conn));
	}

	void Server::handle_accept(const boost::system::error_code &e, pointer conn) {
		if (!e) {
			Message *request = conn->read();

			if (request->getMessageType() == JaPaMusic::MessageType::TRACK_INFO_REQUEST) {
				MessageTrackRequest *req = (MessageTrackRequest *) request;
				MessageTrackResponse response;

				TrackInfo info = Player::getInfo("Music/" + req->getData());
				response.setData(info);

				conn->write(&response);
			}

			if (request->getMessageType() == JaPaMusic::MessageType::TRACK_DATA_REQUEST) {
				MessageDataRequest *req = (MessageDataRequest *) request;
				MessageDataResponse response;

				TrackInfo info = req->getData();
				float *buffer = new float[MUSIC_BUFFER_FRAMES * info.channels];
				Player::getMusicData(info.filename.c_str(), info.currentFrame, buffer, MUSIC_BUFFER_FRAMES);

				response.setData(buffer, MUSIC_BUFFER_FRAMES * info.channels);

				conn->write(&response);
				delete[] buffer;
			}

			if (request->getMessageType() == JaPaMusic::MessageType::TRACK_FILES_REQUEST) {
				MessageFilesRequest *req = (MessageFilesRequest *) request;
				MessageFilesResponse response;

				std::vector<std::string> files;
				for (const auto &entry : std::filesystem::directory_iterator("Music"))
					if (entry.path().extension() == ".wav")
						files.push_back(entry.path().filename());

				response.setData(files);
				conn->write(&response);
			}

		}

		// Start an accept operation for a new connection.
		pointer new_conn(new Connection(io_context_));
		acceptor_.async_accept(new_conn->socket(),
		                       boost::bind(&Server::handle_accept, this,
		                                   boost::asio::placeholders::error, new_conn));
	}
}


