// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Shader.h"

#include "Makeshift/Debug/Log.h"

#include <json/json.h>

#include <fstream>

#include <imgui/imgui.h>

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

		m_Data.shaderProgram = std::make_shared<ShaderProgram>(m_Data.vertexShaderSource, m_Data.fragmentShaderSource);

	}

	void Shader::save(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Shader::save()");

		Json::Value root;

		root["Vertex Code"] = m_Data.vertexShaderSource;
		root["Fragment Code"] = m_Data.fragmentShaderSource;

		DEBUG_INFO("Writing Shader-File '{}'...", location);

		Json::StyledWriter writer;

		std::ofstream file(location);
		if (file.is_open())
		{
			file << writer.write(root);
			file.close();
		}
		else
		{
			DEBUG_ERROR("Failed to write Shader-File to location '{}'", location);
		}

	}

	void Shader::renderIMGUI()
	{

		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "VertexShader:");
		ImGui::Text(m_Data.vertexShaderSource.c_str());
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "FragmentShader:");
		ImGui::Text(m_Data.fragmentShaderSource.c_str());

	}

}
