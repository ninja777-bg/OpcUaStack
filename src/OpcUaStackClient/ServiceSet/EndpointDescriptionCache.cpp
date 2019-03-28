/*
   Copyright 2019 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackClient/ServiceSet/EndpointDescriptionCache.h"

using namespace OpcUaStackCore;

namespace OpcUaStackClient
{

	EndpointDescriptionCache::EndpointDescriptionCache(void)
	: endpointDescriptionMap_()
	{
	}

	EndpointDescriptionCache::~EndpointDescriptionCache(void)
	{
	}

	void
	EndpointDescriptionCache::clear(void)
	{
		endpointDescriptionMap_.clear();
	}

	void
	EndpointDescriptionCache::insertEndpointDescription(
		const std::string& endpointUrl,
		EndpointDescriptionArray::SPtr& endpointDescriptionArray
	)
	{
		// if an entry already exists then delete it
		deleteEndpointDescription(endpointUrl);

		// insert new entry
		endpointDescriptionMap_.insert(std::make_pair(endpointUrl, endpointDescriptionArray));
	}

	void
	EndpointDescriptionCache::deleteEndpointDescription(
		const std::string& endpointUrl
	)
	{
		auto it = endpointDescriptionMap_.find(endpointUrl);
		if (it != endpointDescriptionMap_.end()) {
			endpointDescriptionMap_.erase(it);
		}
	}

	EndpointDescriptionArray::SPtr
	EndpointDescriptionCache::getEndpointDescription(
		const std::string& endpointUrl
	)
	{
		auto it = endpointDescriptionMap_.find(endpointUrl);
		if (it != endpointDescriptionMap_.end()) {
			return it->second;
		}

		EndpointDescriptionArray::SPtr endpointDescriptionArray;
		return endpointDescriptionArray;
	}

}
