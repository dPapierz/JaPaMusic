#include "Client.h"

namespace JaPaMusic {

	Client::Client(boost::asio::io_context &io_context, const std::string &host, const std::string &service) :
		io_context_(io_context),
		connection_(io_context) {
		boost::asio::ip::tcp::resolver resolver(io_context);
		boost::asio::ip::tcp::resolver::query query(host, service);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::connect(connection_.socket(), endpoint_iterator);
	}

	Message *Client::read() {
		return connection_.read();
	}

	std::size_t Client::write(Message *request) {
		return connection_.write(request);
	}
}



