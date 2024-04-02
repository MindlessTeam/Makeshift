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

}
