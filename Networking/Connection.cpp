#include "Connection.h"

namespace JaPaMusic {

	Connection::Connection(boost::asio::io_context &io_context) :
		socket_(io_context) {
	}

	std::size_t Connection::write(Message *request) {
		// Serialize the data first so we know how large it is.

		std::ostringstream archive_stream;
		boost::archive::text_oarchive archive(archive_stream);
		archive << request;
		outbound_data_ = archive_stream.str();

		// Format the header.
		std::ostringstream header_stream;
		header_stream << std::setw(header_length)
		              << std::hex << outbound_data_.size();
		if (!header_stream || header_stream.str().size() != header_length) {
			// Something went wrong, inform the caller.
			return 0;
		}
		outbound_header_ = header_stream.str();

		// Write the serialized data to the socket. We use "gather-write" to send
		// both the header and the data in a single write operation.
		std::vector<boost::asio::const_buffer> buffers;
		buffers.push_back(boost::asio::buffer(outbound_header_));
		buffers.push_back(boost::asio::buffer(outbound_data_));

		return boost::asio::write(socket_, buffers);
	}

	Message *Connection::read() {
		boost::system::error_code error;
		boost::asio::read(socket_, boost::asio::buffer(inbound_header_), error);

		std::istringstream is(std::string(inbound_header_, header_length));
		std::size_t inbound_data_size = 0;
		if (!(is >> std::hex >> inbound_data_size)) {
			return 0;
		}

		inbound_data_.resize(inbound_data_size);
		boost::asio::read(socket_, boost::asio::buffer(inbound_data_), boost::asio::transfer_exactly(inbound_data_size));

		Message *response = nullptr;

		try {
			std::string archive_data(&inbound_data_[0], inbound_data_.size());
			std::istringstream archive_stream(archive_data);
			boost::archive::text_iarchive archive(archive_stream);
			archive >> response;
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() <<std::endl;
			return nullptr;
		}

		return response;
	}
}

































