// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Material.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Makeshift.hpp"

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

		//const Json::Value& materialProperties = root["Material Properties"];
		//if (materialProperties.isNull())
		//{
		//	DEBUG_WARN("No material properties associated with shader {}", m_Data.shader->m_Location);
		//	return;
		//}

		//for (const Json::Value& materialProperty : materialProperties)
		//{
		//}

	}

}
