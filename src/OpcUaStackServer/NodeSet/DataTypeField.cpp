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

#include <boost/lexical_cast.hpp>
#include "OpcUaStackServer/NodeSet/DataTypeField.h"
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaStackServer
{

	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------
	//
	// DataTypeElement
	//
	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------
	DataTypeField::DataTypeField(void)
	: dataSubType_(None)
	, name_()
	, dataType_()
	, valueRank_(-1)
	, description_()
	, dataTypeDefinition_()
	, value_(0)
	, isOptional_(false)
	{
	}

	DataTypeField::~DataTypeField(void)
	{
	}

	DataSubType&
	DataTypeField::dataSubType(void)
	{
		return dataSubType_;
	}

	void
	DataTypeField::dataSubType(DataSubType& dataSubType)
	{
		dataSubType_ = dataSubType;
	}

	OpcUaString&
	DataTypeField::name(void)
	{
		return name_;
	}

	void
	DataTypeField::name(OpcUaString& name)
	{
		name.copyTo(name_);
	}

	OpcUaNodeId&
	DataTypeField::dataType(void)
	{
		return dataType_;
	}

	void
	DataTypeField::dataType(OpcUaNodeId& dataType)
	{
		dataType.copyTo(dataType_);
	}

	OpcUaInt32
	DataTypeField::valueRank(void)
	{
		return valueRank_;
	}

	void
	DataTypeField::valueRank(OpcUaInt32 valueRank)
	{
		valueRank_ = valueRank;
	}

	OpcUaLocalizedText&
	DataTypeField::description(void)
	{
		return description_;
	}

	void
	DataTypeField::description(OpcUaLocalizedText& description)
	{
		description.copyTo(description_);
	}

	Object::SPtr&
	DataTypeField::dataTypeDefinition(void)
	{
		return dataTypeDefinition_;
	}

	void
	DataTypeField::dataTypeDefinition(Object::SPtr& dataTypeDefinition)
	{
		dataTypeDefinition_ = dataTypeDefinition;
	}

	OpcUaInt32
	DataTypeField::value(void)
	{
		return value_;
	}

	void
	DataTypeField::value(OpcUaInt32 value)
	{
		value_ = value;
	}

	OpcUaBoolean
	DataTypeField::isOptional(void)
	{
		return isOptional_;
	}

	void
	DataTypeField::isOptional(OpcUaBoolean isOptional)
	{
		isOptional_ = isOptional;
	}

	bool
	DataTypeField::decode(boost::property_tree::ptree& ptree)
	{
		if (dataSubType_ == Structure) {
			return decodeStruct(ptree);
		}
		else if (dataSubType_ == Enumeration) {
			return decodeEnum(ptree);
		}
		return false;
	}

	bool
	DataTypeField::encode(boost::property_tree::ptree& ptree)
	{
		if (dataSubType_ == Structure) {
			return encodeStruct(ptree);
		}
		else if (dataSubType_ == Enumeration) {
			return decodeEnum(ptree);
		}
		return false;
	}

	bool
	DataTypeField::decodeEnum(boost::property_tree::ptree& ptree)
	{
		// decode name
		ptree.put("<xmlattr>.Name", name_.value());

		// decode description
		if (description_.text().size() > 0) {
			ptree.put("Description", description_.text());
		}

		// decode value
		std::stringstream ss;
		ss << value_;
		ptree.put("<xmlattr>.Value", ss.str());

		return false;
	}

	bool
	DataTypeField::decodeStruct(boost::property_tree::ptree& ptree)
	{
		// decode name
		// decode dataType
		// decode valueRank
		// decode description
		// decode dataTypeDefinition (optional)
		// decode isOptional

		// FIXME: todo
		return false;
	}

	bool
	DataTypeField::encodeEnum(boost::property_tree::ptree& ptree)
	{
		// decode name
		boost::optional<std::string> name = ptree.get_optional<std::string>("<xmlattr>.Name");
		if (!name) {
			Log(Error, "missing attribute in data type field")
				.parameter("Attribute", "Name");
			return false;
		}
		name_.value(*name);

		// decode description (optional)
		boost::optional<std::string> description = ptree.get_optional<std::string>("Description");
		if (description) {
			description_.locale("");
			description_.text(*description);
		}

		// decode value
		boost::optional<std::string> value = ptree.get_optional<std::string>("<xmlattr>.Value");
		if (!value) {
			Log(Error, "missing attribute in data type field")
				.parameter("Attribute", "Value");
			return false;
		}
		try {
			value_ = (OpcUaInt32)boost::lexical_cast<OpcUaUInt32>(*value);
		} catch(boost::bad_lexical_cast& e) {
			Log(Error, "invalid attribute in data type field")
				.parameter("Attribute", "Value")
				.parameter("Value", *value)
				.parameter("What", e.what());
			return false;
		}

		return false;
	}

	bool
	DataTypeField::encodeStruct(boost::property_tree::ptree& ptree)
	{
		// decode name
		// decode dataType
		// decode valueRank
		// decode description (optional)
		// decode dataTypeDefinition (optional)
		// decode isOptional
		// FIXME: todo
		return false;
	}


}