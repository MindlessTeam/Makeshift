// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Editor.h"

#include "Utility/Util.h"
#include "Utility/DragDropTypes.h"

#include "UI/Style.h"
#include "UI/Elements.h"

#include <Makeshift/Graphics/ImGuiRenderer.h>
#include <Makeshift/Core/Engine.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <IconsMaterialSymbols.h>

namespace MakeshiftEditor
{

	Editor* Editor::s_Instance = nullptr;
	
	void Editor::init()
	{
		DEBUG_TRACE("MakeshiftEditor::Editor::init()");

		if (s_Instance == nullptr)
		{
			s_Instance == this;
		}
	
		m_About.setEnabled(false);
	}
	
	void Editor::run()
	{
		DEBUG_TRACE("MakeshiftEditor::Editor::run()");

		ImVec2 mainWindowOrigin = ImGui::GetMainViewport()->Pos;
		ImVec2 mainWindowSize = ImGui::GetMainViewport()->Size;
	
		ImGuiWindowFlags taskbarFlags = ImGuiWindowFlags_None;
		taskbarFlags |= ImGuiWindowFlags_NoDecoration;
		taskbarFlags |= ImGuiWindowFlags_NoScrollbar;
		taskbarFlags |= ImGuiWindowFlags_NoSavedSettings;
		taskbarFlags |= ImGuiWindowFlags_NoDocking;
		taskbarFlags |= ImGuiWindowFlags_NoScrollWithMouse;
		taskbarFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	
		ImGui::PushStyleColor(ImGuiCol_WindowBg, Style::Transparent());
	
		ImGui::SetNextWindowPos(mainWindowOrigin);
		ImGui::SetNextWindowSize(mainWindowSize);
		ImGui::Begin("##WindowOverlay", 0, taskbarFlags);
	
		renderMenuBar();
		renderSideBar();

		ImGui::SameLine();

		if (Elements::BeginDragDropTargetWindow(MAKESHIFT_PAYLOAD_EXTERNAL))
		{

			ImGui::EndDragDropTarget();
		}
	
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, Style::Transparent());
	
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("##Dockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
		}
	
		ImGui::PopStyleColor();
	
		ImGui::End();

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor();
	
		for (auto entry : m_EditorWindows)
		{
			for (auto window : entry.second)
			{
				window->renderIMGUI();
			}
		}
	
		m_About.renderIMGUI();

	}

	void Editor::addEditorWindow(const std::string& menu, std::shared_ptr<EditorWindow> window)
	{
		DEBUG_TRACE("MakeshiftEditor::Editor::addEditorWindow()");

		for (auto entry : m_EditorWindows)
		{
			if (entry.first == menu)
			{
				entry.second.push_back(window);
			}
		}

		std::vector<std::shared_ptr<EditorWindow>> windows;
		windows.push_back(window);

		m_EditorWindows.emplace(menu, windows);

	}

	void Editor::renderMenuBar()
	{
		DEBUG_TRACE("MakeshiftEditor::Editor::renderMenuBar()");

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, Style::LighterOverlay());

		ImGui::BeginChild("##MenuBar", ImVec2(ImGui::GetContentRegionAvail().x, Util::getRequiredVerticalTextSize(1, false) + 4));

		ImGui::Button(ICON_MS_ADD " New");
		ImGui::SameLine();
		ImGui::Button(ICON_MS_FILE_OPEN " Open");
		ImGui::SameLine();
		ImGui::Button(ICON_MS_FILE_SAVE " Save");
		ImGui::SameLine();
		ImGui::Button(ICON_MS_LANDSCAPE " Run ");
		ImGui::SameLine();
		Elements::ItemBorder(1.0f, ImGuiDir_Right, Style::LighterAccent());


		for (auto entry : m_EditorWindows)
		{

			ImVec2 cursorPos = ImVec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y + Util::getRequiredVerticalTextSize(1, false) + 4);

			if (ImGui::Button(entry.first.c_str()))
			{
				ImGui::OpenPopup(std::string(entry.first + "PopUp").c_str());
			}

			ImGui::SetNextWindowPos(cursorPos);
			if (ImGui::BeginPopup(std::string(entry.first + "PopUp").c_str(), ImGuiWindowFlags_AlwaysAutoResize))
			{

				for (auto window : entry.second)
				{
					if (window->getEnabled())
					{
						if (ImGui::Button(std::string(ICON_MS_CHECK_BOX + window->getTitle()).c_str()))
						{
							window->setEnabled(false);
						}
					}
					else
					{
						if (ImGui::Button(std::string(ICON_MS_CHECK_BOX_OUTLINE_BLANK + window->getTitle()).c_str()))
						{
							window->setEnabled(true);
						}
					}
				}

				ImGui::EndPopup();
			}

			ImGui::SameLine();

		}

		float remainingSpace = ImGui::GetContentRegionAvail().x;
		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + remainingSpace - Util::getRequiredVerticalTextSize(5, true) + 5, ImGui::GetCursorPos().y));

		if (ImGui::Button(ICON_MS_INFO))
		{
			m_About.setEnabled(!m_About.getEnabled());
		}
		ImGui::SameLine();
		ImGui::Button(ICON_MS_HELP);
		ImGui::SameLine();
		ImGui::Button(ICON_MS_SETTINGS);
		ImGui::SameLine();
		if (ImGui::Button(ICON_MS_CLOSE))
		{
			Makeshift::Engine::getInstance().quit();
		}

		ImGui::EndChild();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();

	}

	void Editor::renderSideBar()
	{
		DEBUG_TRACE("MakeshiftEditor::Editor::renderSideBar()");

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, Style::LightOverlay());

		ImGui::BeginChild("##SideBar", ImVec2(Util::getRequiredVerticalTextSize(1, false) + 5, ImGui::GetContentRegionAvail().y));

		ImGui::Button(ICON_MS_DEPLOYED_CODE);
		ImGui::Button(ICON_MS_LIST);
		ImGui::Separator();
		ImGui::Button(ICON_MS_BRUSH);
		ImGui::Button(ICON_MS_INVENTORY_2);
		ImGui::Button(ICON_MS_LIGHTBULB);
		ImGui::Button(ICON_MS_FILTER_DRAMA);
		ImGui::Button(ICON_MS_SPEAKER);
		ImGui::Button(ICON_MS_PSYCHOLOGY);
		ImGui::Button(ICON_MS_GRADIENT);

		ImGui::EndChild();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();

	}

}
