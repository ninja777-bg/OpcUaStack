/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

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

#ifdef USE_MOSQUITTO_CLIENT

#include "OpcUaStackPubSub/MQTT/MQTTClient.h"

namespace OpcUaStackPubSub
{

	MQTTClient::MQTTClient(void)
	: MQTTClientIf()
	, mqttClient_(nullptr)
	{
	}

	MQTTClient::~MQTTClient(void)
	{
	}

	bool
	MQTTClient::init(void)
	{
		// Initialize the Mosquitto library
		mosquitto_lib_init();

		return true;
	}

	bool
	MQTTClient::cleanup(void)
	{
		 // Tidy up
		  mosquitto_lib_cleanup();

		return true;
	}

	bool
	MQTTClient::startup(void)
	{
		return false;
	}

	bool
	MQTTClient::shutdown(void)
	{
		return false;
	}

	bool
	MQTTClient::mqttClientIfEnabled(void)
	{
		return true;
	}

	MQTTClientIf::SPtr constructMQTT(void)
	{
		return constructSPtr<MQTTClient>();
	}

}

#else

namespace OpcUaStackPubSub
{
	MQTTClientIf::SPtr constructMQTT(void)
	{
		return constructSPtr<MQTTClientIf>();
	}
}

#endif
