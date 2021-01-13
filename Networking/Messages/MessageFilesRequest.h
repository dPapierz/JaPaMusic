#ifndef MESSAGEFILESREQUEST_H
#define MESSAGEFILESREQUEST_H

#include <vector>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

#include "Message.h"

namespace JaPaMusic {

	class MessageFilesRequest : public Message {
		public:
			MessageFilesRequest();
			~MessageFilesRequest();

		private:

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version) {
				// serialize base class information
				ar &boost::serialization::base_object<Message>(*this);
			}
	};

}

BOOST_CLASS_EXPORT_KEY(JaPaMusic::MessageFilesRequest);

#endif // MESSAGEFILESREQUEST_H
