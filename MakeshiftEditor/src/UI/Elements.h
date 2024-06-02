// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace MakeshiftEditor
{

	struct Elements
	{

		static void Border(float thickness, ImGuiDir side, ImVec4 colour = ImVec4(1, 1, 1, 0.1f));
		static void ItemBorder(float thickness, ImGuiDir side, ImVec4 colour = ImVec4(1, 1, 1, 0.1f));

		static void ToolTip(const char* text);

		static void CenteredText(const char* fmt, ...);

		static bool BeginDragDropTargetWindow();
		static bool BeginDragDropTargetWindow(const char* payloadType);


	};

}