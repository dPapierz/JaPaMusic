#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/binary_object.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace JaPaMusic {
	
	enum MessageType {
		UNKNOWN = 0, ERROR,
		TRACK_INFO_REQUEST, TRACK_INFO_RESPONSE,
		TRACK_DATA_REQUEST, TRACK_DATA_RESPONSE,
		TRACK_FILES_REQUEST, TRACK_FILES_RESPONSE
	};

	class Message {
		public:
			Message();
			virtual ~Message() {}

			virtual inline MessageType getMessageType() {
				return type_;
			}

		protected:
			MessageType type_;

		private:

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version) {
				ar &type_;
			}
	};

}
#endif // MESSAGE_H





