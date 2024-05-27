// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "MaterialProperty.h"

namespace Makeshift
{

	std::map<std::string, std::function<std::shared_ptr<MaterialProperty>()>> MaterialPropertyRegistry::s_MaterialPropertyRegistry;

	std::shared_ptr<MaterialProperty> MaterialPropertyRegistry::createMaterialProperty(const std::string& name)
	{
		DEBUG_TRACE("Makeshift::MaterialPropertyRegistry::createMaterialProperty()");

		auto property = s_MaterialPropertyRegistry.find(name);
		if (property != s_MaterialPropertyRegistry.end())
		{
			return std::dynamic_pointer_cast<MaterialProperty>((property->second)());
		}

		DEBUG_WARN("Couldn't create Material Property of type '{}'. Property is not registered!", name);

	}

}