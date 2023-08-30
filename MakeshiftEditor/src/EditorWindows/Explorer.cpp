// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Explorer.h"

#include <imgui/imgui.h>

namespace MakeshiftEditor
{

	Explorer::Explorer()
	{

		m_RootDirectory = std::filesystem::current_path();
		m_CurrentDirectory = m_RootDirectory;

	}

	void Explorer::renderIMGUI()
	{

		ImGui::Begin("Explorer");

		if (m_CurrentDirectory != std::filesystem::path(m_RootDirectory))
		{
			if (ImGui::ArrowButton("Return", ImGuiDir_Left))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			std::string filenameString = path.filename().string();
			
			if (directoryEntry.is_directory())
			{

				ImGui::PushID((filenameString + "text").c_str());
				ImGui::Button(filenameString.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0));

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (directoryEntry.is_directory())
					{
						m_CurrentDirectory /= path.filename();
					}
				}
			}
			else
			{
				ImGui::PushID(filenameString.c_str());
				ImGui::Button(filenameString.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0));
			}
		
			if (ImGui::BeginDragDropSource())
			{
				ImGui::EndDragDropSource();
			}
		
			
		
			ImGui::PopID();
		}

		// TODO: status bar
		ImGui::End();

	}

}