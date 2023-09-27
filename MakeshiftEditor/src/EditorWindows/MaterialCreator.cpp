// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "MaterialCreator.h"

#include "Explorer.h"

#include <Makeshift/Debug/Log.h>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <json/json.h>

#include <fstream>

namespace MakeshiftEditor
{

	void MaterialCreator::renderIMGUI()
	{

		if (enabled)
		{

			ImGui::Begin("Material Creator", &enabled, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
			ImGui::SetWindowSize(ImVec2(612, 0));

			if (ImGui::CollapsingHeader("Shader"))
			{
				ImGui::Checkbox("Create New Shader", &m_CreateNewShader);

				ImGui::InputText("Shader Location", &m_ShaderLocation);
				ImGui::SameLine();
				if (ImGui::Button("Shader Explore"))
				{
					m_ShaderLocation = Explorer::getRelativeCreatedFilePath();
				}

				ImGuiInputTextFlags inputFlags = m_CreateNewShader ? 0 : ImGuiInputTextFlags_ReadOnly;
				
				ImGui::InputTextMultiline("Vertex Code", &m_VertexText, ImVec2(0, 0), inputFlags);
				ImGui::InputTextMultiline("Fragment Code", &m_FragmentText, ImVec2(0,0), inputFlags);
			
			}

			if (ImGui::CollapsingHeader("Material"))
			{

				ImGui::InputText("Material Location", &m_Location);
				ImGui::SameLine();
				if (ImGui::Button("Material Explore"))
				{
					m_Location = Explorer::getRelativeCreatedFilePath();
				}
				if(ImGui::Button("Export Material"))
				{
					if (!m_ShaderLocation.empty() && m_CreateNewShader)
					{
						Json::Value root;

						root["Vertex Code"] = m_VertexText;
						root["Fragment Code"] = m_FragmentText;

						DEBUG_INFO("Writing Shader-File '{}'...", m_ShaderLocation);

						Json::StyledWriter writer;

						std::ofstream file(m_ShaderLocation);
						if (file.is_open())
						{
							file << writer.write(root);
							file.close();
						}
						else
						{
							DEBUG_ERROR("Failed to write Shader-File to location '{}'", m_ShaderLocation);
						}
					}

					if (!m_Location.empty())
					{
						Json::Value root;

						root["Shader Location"] = m_ShaderLocation;

						DEBUG_INFO("Writing Material-File '{}'...", m_Location);

						Json::StyledWriter writer;

						std::ofstream file(m_Location);
						if (file.is_open())
						{
							file << writer.write(root);
							file.close();
						}
						else
						{
							DEBUG_ERROR("Failed to write Material-File to location '{}'", m_Location);
						}
					}
				}

			}


			ImGui::End();

		}

	}

}