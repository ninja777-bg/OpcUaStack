#ifndef __OpcUaStackCore_HistoryReadValueId_h__
#define __OpcUaStackCore_HistoryReadValueId_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaArray.h"

namespace OpcUaStackCore
{

	class DLLEXPORT HistoryReadValueId : public  ObjectPool<HistoryReadValueId>
	{
	  public:
		typedef boost::shared_ptr<HistoryReadValueId> SPtr;

		HistoryReadValueId(void);
		virtual ~HistoryReadValueId(void);

		void nodeId(const OpcUaNodeId::SPtr nodeId);
		OpcUaNodeId::SPtr nodeId(void);
		void indexRange(const OpcUaString& indexRange);
		std::string indexRange(void) const;
		void dataEncoding(const OpcUaQualifiedName& dataEncoding);
		OpcUaQualifiedName& dataEncoding(void);
		void continuationPoint(const OpcUaByteString& continuationPoint);
		OpcUaByteString& continuationPoint(void);

		void nodeId(const OpcUaInt16& namespaceId, const OpcUaInt32& identifier);
		void indexRange(const std::string& value);
		void dataEncoding(const OpcUaInt16& namespaceIndex, const std::string& name);
		void dataEncoding(const std::string& name);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		OpcUaNodeId::SPtr nodeIdSPtr_;
		OpcUaString indexRange_;
		OpcUaQualifiedName dataEncoding_;
		OpcUaByteString continuationPoint_;
	};

	class HistoryReadValueIdArray : public OpcUaArray<HistoryReadValueId::SPtr, SPtrTypeCoder<HistoryReadValueId> >, public ObjectPool<HistoryReadValueIdArray> 
	{
	  public:
		typedef boost::shared_ptr<HistoryReadValueIdArray> SPtr;
	};

}

#endif