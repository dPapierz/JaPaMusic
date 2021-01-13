#ifndef MESSAGEFILESRESPONSE_H
#define MESSAGEFILESRESPONSE_H

#include <vector>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include "Message.h"

namespace JaPaMusic {

	class MessageFilesResponse : public Message {
		public:
			MessageFilesResponse();
			~MessageFilesResponse();

			inline void setData(std::vector<std::string> buffer) {
				buffer_ = buffer;
			}

			inline std::vector<std::string> getData() {
				return buffer_;
			}

		private:
			std::vector<std::string> buffer_;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version) {
				// serialize base class information
				ar &boost::serialization::base_object<Message>(*this);
				ar &buffer_;
			}
	};

}

BOOST_CLASS_EXPORT_KEY(JaPaMusic::MessageFilesResponse);

#endif // MESSAGEFILESRESPONSE_H
