// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Material.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Makeshift.hpp"
#include "Makeshift/Version.h"

#include <glad/glad.h>

#include <fstream>
#include <json/json.h>

namespace Makeshift
{

	void Material::loadJson(Json::Value root)
	{
		DEBUG_TRACE("Makeshift::Material::loadJson()");

		m_Data.shader = Engine::getInstance().getResourceMap()->addResource<Shader>(root["Shader Location"].asString());

		const Json::Value& materialProperties = root["Material Properties"];
		if (materialProperties.isNull())
		{
			DEBUG_WARN("No material properties associated with shader {}", m_Data.shader->m_Location);
			return;
		}
		
		for (const Json::Value& materialProperty : materialProperties)
		{

			//TODO: Material Property Implementation
			
		}

	}


}
