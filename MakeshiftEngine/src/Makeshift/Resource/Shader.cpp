// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Shader.h"

#include "Makeshift/Debug/Log.h"

#include <json/json.h>

#include <fstream>

namespace Makeshift
{

	void Shader::load(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Shader::load()");

		DEBUG_INFO("Loading Shader '{}'", location);

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

		m_Data.vertexShaderSource = root["Vertex Code"].asString();
		m_Data.fragmentShaderSource = root["Fragment Code"].asString();

	}

}
