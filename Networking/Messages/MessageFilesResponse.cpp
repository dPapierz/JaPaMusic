#include "MessageFilesResponse.h"

BOOST_CLASS_EXPORT_IMPLEMENT(JaPaMusic::MessageFilesResponse);

namespace JaPaMusic {

	MessageFilesResponse::MessageFilesResponse() {
		type_ = MessageType::TRACK_FILES_RESPONSE;
	}

	MessageFilesResponse::~MessageFilesResponse() {}

}
