/*
   Copyright 2015-2017 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackServer_SecureChannelTransactionOld_h__
#define __OpcUaStackServer_SecureChannelTransactionOld_h__

#include <boost/shared_ptr.hpp>
#include <boost/asio/streambuf.hpp>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNumber.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include <stdint.h>
#include <list>

using namespace OpcUaStackCore;

namespace OpcUaStackServer
{

	class DLLEXPORT SecureChannelTransactionOld
	: public Object
	{
	  public:
		typedef boost::shared_ptr<SecureChannelTransactionOld> SPtr;
		typedef std::list<SecureChannelTransactionOld::SPtr> List;

	    SecureChannelTransactionOld(void);
	    ~SecureChannelTransactionOld(void);

	    void isAppend(boost::asio::streambuf& sb);
	    void osAppend(boost::asio::streambuf& sb);

		OpcUaNodeId requestTypeNodeId_;
		OpcUaNodeId responseTypeNodeId_;
		uint32_t requestId_;
		OpcUaUInt32 channelId_;
		OpcUaUInt32 authenticationToken_;

		boost::asio::streambuf is_;
		boost::asio::streambuf os_;
	};

}

#endif
