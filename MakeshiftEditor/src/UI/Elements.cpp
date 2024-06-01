// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Elements.h"

namespace MakeshiftEditor
{

	void Elements::Border(float thickness, ImGuiDir side, ImVec4 colour)
	{

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		// Calculate the positions for the line
		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 windowSize = ImGui::GetWindowSize();

		ImVec2 lineStart;
		ImVec2 lineEnd;

		// Make enough space to show the entire line
		float padding = thickness / 2.0f;

		if (side == ImGuiDir_Up)
		{
			lineStart = ImVec2(windowPos.x, windowPos.y + padding); // Top-Left + padding
			lineEnd = ImVec2(windowPos.x + windowSize.x, windowPos.y + padding); // Top-Right + padding
		}
		else if (side == ImGuiDir_Down)
		{
			lineStart = ImVec2(windowPos.x, windowPos.y + windowSize.y - padding); // Bottom-Left + padding
			lineEnd = ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y - padding); // Bottom-Right + padding
		}
		else if (side == ImGuiDir_Left)
		{
			lineStart = ImVec2(windowPos.x + padding, windowPos.y); // Top-Left + padding
			lineEnd = ImVec2(windowPos.x + padding, windowPos.y + windowSize.y); // Bottom-Left + padding
		}
		else if (side == ImGuiDir_Right)
		{
			lineStart = ImVec2(windowPos.x + windowSize.x - padding, windowPos.y); // Top-Right + padding
			lineEnd = ImVec2(windowPos.x + windowSize.x - padding, windowPos.y + windowSize.y); // Bottom-Right + padding
		}		

		drawList->AddLine(lineStart, lineEnd, IM_COL32(colour.x * 255, colour.y * 255, colour.z * 255, colour.w * 255), thickness);

	}

	void Elements::ToolTip(const char* text)
	{

		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled | ImGuiHoveredFlags_DelayNormal))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 5));
			ImGui::SetTooltip(text);
			ImGui::PopStyleVar();
		}

	}

	void Elements::CenteredText(const char* fmt, ...)
	{
		const char* text, * text_end;

		va_list args;
		va_start(args, fmt);
		ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
		va_end(args);

		float areaWidth = ImGui::GetContentRegionAvail().x;
		float padding = ImGui::GetCurrentWindow()->WindowPadding.x;
		float textWidth = ImGui::CalcTextSize(text, text_end, true).x;

		ImGui::SetCursorPos(ImVec2(padding + areaWidth / 2 - (textWidth / 2), ImGui::GetCursorPosY()));
		ImGui::TextEx(text, text_end, ImGuiTextFlags_NoWidthForLargeClippedText);

	}

}