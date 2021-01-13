#include "MessageDataRequest.h"

BOOST_CLASS_EXPORT_IMPLEMENT(JaPaMusic::MessageDataRequest);

namespace JaPaMusic {

	MessageDataRequest::MessageDataRequest() {
		type_ = MessageType::TRACK_DATA_REQUEST;
	}

	MessageDataRequest::~MessageDataRequest() {}

}
