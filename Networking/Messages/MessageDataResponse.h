#ifndef MESSAGEDATARESPONSE_H
#define MESSAGEDATARESPONSE_H

#include <vector>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include "Message.h"

namespace JaPaMusic {

	class MessageDataResponse : public Message   {
		public:
			MessageDataResponse();
			~MessageDataResponse();

			inline void setData(float *buffer, std::size_t size) {
				buffer_.assign(buffer, buffer + size);
			}

			inline std::vector<float> getData() {
				return buffer_;
			}

		private:
			std::vector<float> buffer_;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version) {
				// serialize base class information
				ar &boost::serialization::base_object<Message>(*this);
				ar &buffer_;
			}
	};
}

BOOST_CLASS_EXPORT_KEY(JaPaMusic::MessageDataResponse);

#endif // MESSAGEDATARESPONSE_H

