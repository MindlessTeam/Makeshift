// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "UITestBench.h"

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include "Utility/Util.h"

#include <IconsMaterialDesign.h>

#include <Makeshift/Debug/Log.h>

namespace MakeshiftEditor
{

	void UITestBench::renderIMGUI()
	{
		DEBUG_TRACE("MakeshiftEditor::UITestBench::renderIMGUI()");

		if (!enabled)
			return;

		ImGui::Begin("UI TestBench");

		ImGui::End();

	}

}