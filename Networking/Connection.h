#ifndef CONNECTION_H
#define CONNECTION_H

#include <iomanip>
#include <string>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "Messages/Message.h"

#include "Messages/MessageTrackRequest.h"
#include "Messages/MessageTrackResponse.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace JaPaMusic {

	class Connection {
		public:
			Connection(boost::asio::io_context &io_context);

			inline boost::asio::ip::tcp::socket &socket() {
				return socket_;
			}

			std::size_t write(Message *request);
			Message *read();

		private:
			/// The underlying socket.
			boost::asio::ip::tcp::socket socket_;

			/// The size of a fixed length header.
			enum { header_length = 8 };

			/// Holds an outbound header.
			std::string outbound_header_;

			/// Holds the outbound data.
			std::string outbound_data_;

			/// Holds an inbound header.
			char inbound_header_[header_length];

			/// Holds the inbound data.
			std::vector<char> inbound_data_;

	};

	typedef boost::shared_ptr<Connection> pointer;

}
#endif // CONNECTION_H



