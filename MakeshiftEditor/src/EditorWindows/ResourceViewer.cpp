// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ResourceViewer.h"

#include <Makeshift/Makeshift.hpp>
#include <Makeshift/Resource/Resource.h>

#include <imgui/imgui.h>

namespace MakeshiftEditor
{

	void ResourceViewer::renderIMGUI()
	{

		ImGui::Begin("Resource Viewer");

		ImGui::BeginChild("ResourceListContainer", ImVec2(ImGui::GetContentRegionAvail().x, 0));

		for (auto entity : *Makeshift::Engine::getInstance().getResourceMap()->getResourceMap())
		{

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1, 1));

			ImGui::PushID(entity.first.c_str());
			ImGui::Button(entity.first.c_str(), ImVec2(ImGui::GetContentRegionAvail().x * 0.9f, 0));
			ImGui::PopID();

			ImGui::SameLine();
			ImGui::Button(std::to_string(entity.second.first).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0));

			ImGui::PopStyleVar();

		}

		ImGui::EndChild();

		ImGui::End();

	}

}