#ifndef __OpcUaStackCore_CancelRequest_h__
#define __OpcUaStackCore_CancelRequest_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/RequestHeader.h"

namespace OpcUaStackCore
{

	class DLLEXPORT CancelRequest : public  ObjectPool<CancelRequest>
	{
	  public:
		typedef boost::shared_ptr<CancelRequest> SPtr;

		CancelRequest(void);
		virtual ~CancelRequest(void);

		void requestHeader(const RequestHeader::SPtr requestHeaderSPtr);
		RequestHeader::SPtr requestHeader(void) const;
		void requestHandle(const IntegerId requestHandle);
		IntegerId requestHandle(void) const;

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		RequestHeader::SPtr requestHeaderSPtr_;
		IntegerId requestHandle_;
	};

}

#endif
