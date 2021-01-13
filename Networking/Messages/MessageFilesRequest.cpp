#include "MessageFilesRequest.h"

BOOST_CLASS_EXPORT_IMPLEMENT(JaPaMusic::MessageFilesRequest);

namespace JaPaMusic {

	MessageFilesRequest::MessageFilesRequest() {
		type_ = MessageType::TRACK_FILES_REQUEST;
	}

	MessageFilesRequest::~MessageFilesRequest() {}

}
