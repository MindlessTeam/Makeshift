// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Material.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Makeshift.hpp"

#include <glad/glad.h>

#include <fstream>
#include <json/json.h>

namespace Makeshift
{

	void Material::load(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Material::load()");

		DEBUG_INFO("Loading Material '{}'", location);

		std::ifstream file(location);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open JSON file '{}'", location);
			return;
		}

		Json::CharReaderBuilder reader;
		std::string errors;

		Json::Value root;

		if (!Json::parseFromStream(reader, file, &root, &errors))
		{
			file.close();
			DEBUG_ERROR("Failed to parse JSON from file '{}' with errors '{}'", location, errors);
			return;
		}

		file.close();

		m_Data.shader = Engine::getInstance().getResourceMap()->addResource<Shader>(root["Shader Location"].asString());

		const Json::Value& materialProperties = root["Material Properties"];
		if (materialProperties.isNull())
		{
			DEBUG_WARN("No material properties associated with shader {}", m_Data.shader->m_Location);
			return;
		}

		if (materialProperties.isNull())
		{
			return;
		}
		
		for (const Json::Value& materialProperty : materialProperties)
		{

			std::shared_ptr<MaterialProperty> property = MaterialProperty::create(materialProperty["Property Type"].asString());
			property->deSerialize(&materialProperty["Data"]);

			property->location = glGetUniformLocation(m_Data.shader->getData().shaderProgram->getRenderID(), property->uniformName.c_str());

			m_Data.materialProperties.push_back(property);
			
		}

	}

	void Material::save(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Material::save()");

		Json::Value root;
		
		root["Shader Location"] = m_Data.shader->m_Location;

		Json::Value materialProperties;
		for (auto& materialProperty : m_Data.materialProperties)
		{
			Json::Value matProp;
			materialProperty->serialize(matProp);
			materialProperties.append(matProp);
		}

		root["Material Properties"] = materialProperties;
		
		DEBUG_INFO("Writing Material-File '{}'...", location);

		Json::StyledWriter writer;

		std::ofstream file(location);
		if (file.is_open())
		{
			file << writer.write(root);
			file.close();
		}
		else
		{
			DEBUG_ERROR("Failed to write Material-File to location '{}'", location);
		}

	}

	void Material::renderIMGUI()
	{

		ImGui::Text(m_Data.shader->m_Location.c_str());

	}

	// -----------------------------

	std::shared_ptr<MaterialProperty> MaterialProperty::create(std::string propertyType)
	{
		if (propertyType == "Float")
			return std::shared_ptr<MaterialPropertyFloat>();
		else if (propertyType == "Int")
			return std::shared_ptr<MaterialPropertyInt>();
		else if (propertyType == "Bool")
			return std::shared_ptr<MaterialPropertyBool>();
	}

	void MaterialPropertyFloat::serialize(Json::Value& JsonValue)
	{
		JsonValue["Property Type"] = std::string("Float");

		Json::Value data;

		data["Value"] = value;

		JsonValue["Data"] = data;
	}
	void MaterialPropertyFloat::deSerialize(const Json::Value& JsonValue)
	{
		value = JsonValue["Value"].asFloat();
	}

	void MaterialPropertyInt::serialize(Json::Value& JsonValue)
	{
		JsonValue["Property Type"] = std::string("Int");

		Json::Value data;

		data["Value"] = value;

		JsonValue["Data"] = data;
	}
	void MaterialPropertyInt::deSerialize(const Json::Value& JsonValue)
	{
		value = JsonValue["Value"].asInt();
	}

	void MaterialPropertyBool::serialize(Json::Value& JsonValue)
	{
		JsonValue["Property Type"] = std::string("Bool");

		Json::Value data;

		data["Value"] = value;

		JsonValue["Data"] = data;
	}
	void MaterialPropertyBool::deSerialize(const Json::Value& JsonValue)
	{
		value = JsonValue["Value"].asBool();
	}


}
