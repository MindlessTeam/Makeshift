// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "LevelMap.h"

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <Makeshift/Core/Engine.h>

#include <Makeshift/Resource/ResourceMap.h>

namespace MakeshiftEditor
{

	void LevelMap::renderIMGUI()
	{
		DEBUG_TRACE("MakeshiftEditor::LevelMap::renderIMGUI()");

		if (!enabled)
			return;

		ImGui::Begin("Level Map", &enabled);

		for (auto resource : Makeshift::Engine::getInstance().getResourceMap()->getResources())
		{
			ImGui::Text("%s | %s | %x", resource.first.c_str(), resource.second.second->getType().c_str(), resource.second.first);
		}

		ImGui::End();

	}

}