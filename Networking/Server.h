#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <filesystem>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "Connection.h"
#include "Messages/Message.h"
#include "../Player/Player.h"

#include "Messages/MessageTrackRequest.h"
#include "Messages/MessageTrackResponse.h"

#include "Messages/MessageDataRequest.h"
#include "Messages/MessageDataResponse.h"

#include "Messages/MessageFilesRequest.h"
#include "Messages/MessageFilesResponse.h"

namespace JaPaMusic {

	class Server {
		public:
			Server(boost::asio::io_context &io_context, unsigned short port);

			void handle_accept(const boost::system::error_code &e, pointer conn);
			void handle_write(const boost::system::error_code &e);

		private:
			boost::asio::io_context &io_context_;
			boost::asio::ip::tcp::acceptor acceptor_;

	};

}
#endif // SERVER_H
