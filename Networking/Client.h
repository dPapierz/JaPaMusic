#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <boost/asio.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Connection.h"
#include "Messages/Message.h"

namespace JaPaMusic {

	class Client {

		public:
			Client(boost::asio::io_context &io_context, const std::string &host, const std::string &service);

			Message *read();
			std::size_t write(Message *request);

		private:
			boost::asio::io_context &io_context_;
			Connection connection_;
	};

}

#endif // CLIENT_H
