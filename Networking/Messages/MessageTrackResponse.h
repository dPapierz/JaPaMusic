#ifndef MESSAGETRACKRESPONSE_H
#define MESSAGETRACKRESPONSE_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include "Message.h"
#include "../../Utility/Structs.h"

namespace JaPaMusic {

	class MessageTrackResponse : public Message {
		public:
			MessageTrackResponse();
			~MessageTrackResponse();

			inline void setData(TrackInfo info) {
				info_ = info;
			}

			inline TrackInfo getData() {
				return info_;
			}

		private:
			TrackInfo info_;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version) {
				// serialize base class information
				ar &boost::serialization::base_object<Message>(*this);
				ar &info_;
			}

	};

}

BOOST_CLASS_EXPORT_KEY(JaPaMusic::MessageTrackResponse);

#endif // MESSAGETRACKRESPONSE_H
