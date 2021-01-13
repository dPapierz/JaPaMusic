#include "MessageDataResponse.h"

BOOST_CLASS_EXPORT_IMPLEMENT(JaPaMusic::MessageDataResponse);

namespace JaPaMusic {

	MessageDataResponse::MessageDataResponse() {
		type_ = MessageType::TRACK_DATA_RESPONSE;
	}

	MessageDataResponse::~MessageDataResponse() {}

}
