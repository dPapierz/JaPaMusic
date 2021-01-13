#include <iostream>
#include <boost/asio.hpp>

#include "Networking/Server.h"

int main(int argc, char *argv[]) {
	try {
		boost::asio::io_context io_context;

		JaPaMusic::Server server(io_context, 9999);
		io_context.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
