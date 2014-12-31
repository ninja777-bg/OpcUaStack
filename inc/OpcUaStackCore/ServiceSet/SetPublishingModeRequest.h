#ifndef __OpcUaStackCore_SetPublishingModeRequest_h__
#define __OpcUaStackCore_SetPublishingModeRequest_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"

namespace OpcUaStackCore
{

	class DLLEXPORT SetPublishingModeRequest : public  ObjectPool<SetPublishingModeRequest>
	{
	  public:
		typedef boost::shared_ptr<SetPublishingModeRequest> SPtr;

		SetPublishingModeRequest(void);
		virtual ~SetPublishingModeRequest(void);

		void publishingEnabled(const OpcUaBoolean& publishingEnabled);
		OpcUaBoolean publishingEnabled(void) const;
		void subscriptionIds(const OpcUaUInt32Array::SPtr subscriptionIds);
		OpcUaUInt32Array::SPtr subscriptionIds(void) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaBoolean publishingEnabled_;
		OpcUaUInt32Array::SPtr subscriptionIdArraySPtr_;
	};

}

#endif