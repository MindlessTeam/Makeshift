// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "LevelEditor.h"

#include "Explorer.h"

#include <Makeshift/Debug/Log.h>

#define EDITOR
#include <Makeshift/Core/Engine.h>
#include <Makeshift/Level/Level.h>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <json/json.h>


namespace MakeshiftEditor
{

	void LevelEditor::renderIMGUI()
	{

		if (enabled)
		{

			ImGui::Begin("Level Editor");

			if (ImGui::CollapsingHeader("LevelMap"))
			{

				for (const auto& pair : *Makeshift::EntityRegistry::getRegistry())
				{

					if (ImGui::Button(pair.first.c_str()))
					{
						std::shared_ptr<Makeshift::Entity> entt = Makeshift::EntityRegistry::createEntity(pair.first);
						Makeshift::Engine::getInstance().getActiveLevel()->addEntity(entt);
					}

				}

				ImGui::Separator();

				for (const auto entity : *Makeshift::Engine::getInstance().getActiveLevel()->getEntityMap())
				{

					if (ImGui::Button(std::to_string(entity.first).c_str()))
					{
						m_CurrentlyInspecting = entity.first;
					}

				}

			}

			ImGui::End();

		}

	}

}