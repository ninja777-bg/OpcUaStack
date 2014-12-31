#ifndef __OpcUaStackCore_MonitoredItemModifyResult_h__
#define __OpcUaStackCore_MonitoredItemModifyResult_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaArray.h"
#include "OpcUaStackCore/ServiceSet/ExtensibleParameter.h"

namespace OpcUaStackCore
{

	class DLLEXPORT MonitoredItemModifyResult : public  ObjectPool<MonitoredItemModifyResult>
	{
	  public:
		typedef boost::shared_ptr<MonitoredItemModifyResult> SPtr;

		MonitoredItemModifyResult(void);
		virtual ~MonitoredItemModifyResult(void);

		void statusCode(const OpcUaStatusCode& statusCode);
		OpcUaStatusCode statusCode(void) const;
		void monitoredItemId(const OpcUaUInt32& monitoredItemId);
		OpcUaUInt32 monitoredItemId(void) const;
		void revisedSamplingInterval(const OpcUaDouble& revisedSamplingInterval);
		OpcUaDouble revisedSamplingInterval(void) const;
		void revisedQueueSize(const OpcUaUInt32& revisedQueueSize);
		OpcUaUInt32 revisedQueueSize(void) const;
		void filterResult(const ExtensibleParameter& filterResult);
		ExtensibleParameter& filterResult(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaStatusCode statusCode_;
		OpcUaDouble revisedSamplingInterval_;
		OpcUaUInt32 revisedQueueSize_;
		ExtensibleParameter filterResult_;
	};

	class MonitoredItemModifyResultArray : public OpcUaArray<MonitoredItemModifyResult::SPtr, SPtrTypeCoder<MonitoredItemModifyResult> >, public ObjectPool<MonitoredItemModifyResultArray> 
	{
	  public:
		typedef boost::shared_ptr<MonitoredItemModifyResultArray> SPtr;
	};

}

#endif