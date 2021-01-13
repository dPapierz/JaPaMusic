#ifndef MESSAGETRACKREQUEST_H
#define MESSAGETRACKREQUEST_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include "Message.h"

namespace JaPaMusic {

	class MessageTrackRequest : public Message {
		public:
			MessageTrackRequest();
			~MessageTrackRequest();

			inline void setData(std::string trackName) {
				trackName_ = trackName;
			}

			inline std::string getData() {
				return trackName_;
			}

		private:
			std::string trackName_;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version) {
				// serialize base class information
				ar &boost::serialization::base_object<Message>(*this);
				ar &trackName_;
			}

	};
	
}

BOOST_CLASS_EXPORT_KEY(JaPaMusic::MessageTrackRequest);

#endif // MESSAGETRACKREQUEST_H

