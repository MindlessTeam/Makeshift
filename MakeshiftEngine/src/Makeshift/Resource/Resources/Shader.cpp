// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Shader.h"

#include "Makeshift/Debug/Log.h"
#include "Makeshift/Version.h"

#include <json/json.h>

#include <fstream>

#include <imgui/imgui.h>

namespace Makeshift
{

	void Shader::loadJson(Json::Value root)
	{
		DEBUG_TRACE("Makeshift::Shader::loadJson()");

		std::string vertexShaderSource = root["Vertex Code"].asString();
		std::string fragmentShaderSource = root["Fragment Code"].asString();

		m_Data.shaderProgram = std::make_shared<OpenGL::ShaderProgram>(vertexShaderSource, fragmentShaderSource);

	}

	void Shader::saveShader(const std::string& location, const std::string& vertexCode, const std::string& fragmentCode)
	{

		Json::Value root;

		root["Type"] = "Texture";
		root["Version"]["major"] = VERSION_MAJOR;
		root["Version"]["minor"] = VERSION_MINOR;
		root["Version"]["patch"] = VERSION_PATCH;

		root["Vertex Code"] = vertexCode;
		root["Fragment Code"] = fragmentCode;

		std::ofstream file(location);
		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open file '{}' for writing!", location);
			file.close();
			return;
		}

		Json::StyledWriter writer;
		file << writer.write(root);
		file.close();

	}

}
