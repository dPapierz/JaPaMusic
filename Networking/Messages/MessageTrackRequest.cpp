#include "MessageTrackRequest.h"

BOOST_CLASS_EXPORT_IMPLEMENT(JaPaMusic::MessageTrackRequest);

namespace JaPaMusic {

	MessageTrackRequest::MessageTrackRequest() {
		type_ = MessageType::TRACK_INFO_REQUEST;
	}

	MessageTrackRequest::~MessageTrackRequest() {}
}
