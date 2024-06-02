// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Elements.h"

#include <imgui/imgui_internal.h>

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

	void Elements::ItemBorder(float thickness, ImGuiDir side, ImVec4 colour)
	{

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImVec2 itemRectMin = ImGui::GetItemRectMin();
		ImVec2 itemRectMax = ImGui::GetItemRectMax();

		ImVec2 lineStart;
		ImVec2 lineEnd;

		// Make enough space to show the entire line
		float padding = thickness / 2.0f;

		if (side == ImGuiDir_Up)
		{
			lineStart = ImVec2(itemRectMin.x, itemRectMin.y + padding); // Top-Left + padding
			lineEnd = ImVec2(itemRectMax.x, itemRectMin.y + padding); // Top-Right + padding
		}
		else if (side == ImGuiDir_Down)
		{
			lineStart = ImVec2(itemRectMin.x, itemRectMax.y - padding); // Bottom-Left + padding
			lineEnd = ImVec2(itemRectMax.x, itemRectMax.y - padding); // Bottom-Right + padding
		}
		else if (side == ImGuiDir_Left)
		{
			lineStart = ImVec2(itemRectMin.x + padding, itemRectMin.y); // Top-Left + padding
			lineEnd = ImVec2(itemRectMin.x + padding, itemRectMax.y); // Bottom-Left + padding
		}
		else if (side == ImGuiDir_Right)
		{
			lineStart = ImVec2(itemRectMax.x - padding, itemRectMin.y); // Top-Right + padding
			lineEnd = ImVec2(itemRectMax.x - padding, itemRectMax.y); // Bottom-Right + padding
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

	bool Elements::BeginDragDropTargetWindow()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (!window)
			return false;

		ImRect innerRect = ImGui::GetCurrentWindow()->InnerRect;

		if (ImGui::BeginDragDropTargetCustom(innerRect, ImGui::GetID("##WindowBgArea")))
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(nullptr, ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
			{
				if (payload->IsPreview())
				{
					ImDrawList* draw_list = ImGui::GetForegroundDrawList();
					draw_list->AddRectFilled(innerRect.Min, innerRect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
					draw_list->AddRect(innerRect.Min, innerRect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
				}
				if (payload->IsDelivery())
					return true;
				ImGui::EndDragDropTarget();
			}
		return false;
	}

	bool Elements::BeginDragDropTargetWindow(const char* payloadType)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (!window)
			return false;

		ImRect innerRect = window->InnerRect;

		if (ImGui::BeginDragDropTargetCustom(innerRect, ImGui::GetID("##WindowBgArea")))
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadType, ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
			if (payload)
			{
				if (payload->IsPreview())
				{
					ImDrawList* draw_list = ImGui::GetForegroundDrawList();
					draw_list->AddRectFilled(innerRect.Min, innerRect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
					draw_list->AddRect(innerRect.Min, innerRect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
				}
				if (payload->IsDelivery())
					return true;
			}
			ImGui::EndDragDropTarget();
		}
		return false;
	}

}