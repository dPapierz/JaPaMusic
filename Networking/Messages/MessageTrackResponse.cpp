#include "MessageTrackResponse.h"

BOOST_CLASS_EXPORT_IMPLEMENT(JaPaMusic::MessageTrackResponse);

namespace JaPaMusic {

	MessageTrackResponse::MessageTrackResponse() {
		type_ = MessageType::TRACK_INFO_RESPONSE;
	}
	
	MessageTrackResponse::~MessageTrackResponse() {}
}
