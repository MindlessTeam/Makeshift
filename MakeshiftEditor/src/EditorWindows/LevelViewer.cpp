// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "LevelViewer.h"

#include <Makeshift/Makeshift.hpp>
#include <Makeshift/Level/Level.h>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

namespace MakeshiftEditor
{

	void LevelViewer::renderIMGUI()
	{

		ImGui::Begin("Level");

		ImGui::InputText("Level Name", Makeshift::Engine::getInstance().getActiveLevel()->getLevelNamePointer());

		if (ImGui::Button("Save"))
		{
			Makeshift::Engine::getInstance().quickSave();
		}

		for (auto registryEntry : *Makeshift::EntityRegistry::getRegistry())
		{

			ImGui::PushID(registryEntry.first.c_str());
			if (ImGui::Button(registryEntry.first.c_str()))
			{
				std::shared_ptr<Makeshift::Entity> entity = Makeshift::EntityRegistry::createEntity(registryEntry.first);

				Makeshift::Engine::getInstance().getActiveLevel()->addEntity(entity);
			}
			ImGui::PopID();

			// This is horrible code that I wish I had never written.

		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 0));
		ImGui::BeginChild("LevelList");
		ImGui::PopStyleVar();

		for (auto entity : *Makeshift::Engine::getInstance().getActiveLevel()->getEntityMap())
		{

			ImGui::PushID((std::to_string(entity.first) + "ID").c_str());
			ImGui::Text(std::to_string(entity.first).c_str());
			ImGui::PopID();

			ImGui::PushID((std::to_string(entity.first) + "Name").c_str());
			ImGui::Text(entity.second->getName().c_str());
			ImGui::PopID();

			ImGui::SameLine();
			ImGui::PushID((std::to_string(entity.first) + "Delete").c_str());
			if (ImGui::Button("Delete"))
			{
				Makeshift::Engine::getInstance().getActiveLevel()->removeEntity(entity.first);
				ImGui::PopID();
				break;
			}
			ImGui::PopID();

			ImGui::Separator();

		}

		ImGui::EndChild();

		ImGui::BeginChild("Entity");

		ImGui::EndChild();

		ImGui::End();

	}

}