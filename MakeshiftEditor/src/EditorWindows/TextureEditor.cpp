// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "TextureEditor.h"

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <imgui/imgui_internal.h>

#include <codecvt>
#include <locale>

#include <IconsMaterialDesign.h>

#include "Utility/Util.h"
#include <Makeshift/Core/Time.h>

#include <iostream>
#include <fstream>

namespace MakeshiftEditor
{

	void flag()
	{
		_sleep(5000);
	}

	void TextureEditor::renderIMGUI()
	{

		if (m_FlagCreation)
		{
			m_TimeSinceFlag += Makeshift::Time::getDeltaTime();

			if (m_FlagCreation && m_TimeSinceFlag >= 0.2f)
			{
				flag();
				m_FlagCreation = false;
				m_TimeSinceFlag = 0;
			}
		}	

		if (!enabled)
			return;

		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
		ImGui::Begin("Texture Editor", &enabled);

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.05, 0.05f, 0.075f, 1.0f));

		ImGui::BeginChild("Buttons", ImVec2(ImGui::GetContentRegionAvail().x, Util::getRequiredVerticalTextSize(1, true)));
		ImGui::PushFont(Makeshift::ImGuiRenderer::getIconFont());

		ImGui::Button(ICON_MD_FILE_OPEN);
		ImGui::SameLine();
		if (ImGui::Button(ICON_MD_SAVE))
		{
			m_FlagCreation = true;

			ImGui::OpenPopup("CompileTexturePopup");

		}
		ImGui::SameLine(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - Util::getRequiredVerticalTextSize(1, true)));
		ImGui::Button(ICON_MD_REFRESH);

		ImGui::PopFont();

		if (ImGui::BeginPopupModal("CompileTexturePopup", &m_FlagCreation, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("Compiling Texture...");

			ImGui::PushFont(Makeshift::ImGuiRenderer::getIconFont());

			ImGui::Text(ICON_MD_PENDING);

			ImGui::PopFont();

			ImGui::EndPopup();
		}

		ImGui::EndChild();

		ImGui::BeginChild("Settings", ImVec2(150, ImGui::GetContentRegionAvail().y), ImGuiChildFlags_ResizeX);

		if (ImGui::CollapsingHeader(ICON_MD_INFO " File Info"))
		{


		}

		if (ImGui::CollapsingHeader(ICON_MD_TEXTURE " Texture Settings"))
		{



		}

		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("Texture Preview");

		float buttonSize = Util::getRequiredVerticalTextSize(1, true);
		ImVec2 areaSize = ImGui::GetContentRegionAvail();
		ImVec2 cursorPos;

		cursorPos.x = ImGui::GetCursorPosX() + areaSize.x / 2 - buttonSize / 2;
		cursorPos.y = ImGui::GetCursorPosY() + areaSize.y / 2 - buttonSize / 2;

		ImGui::SetCursorPos(cursorPos);
		ImGui::PushFont(Makeshift::ImGuiRenderer::getIconFont());

		ImGui::Button(ICON_MD_IMAGE_NOT_SUPPORTED);

		ImGui::PopFont();

		ImGui::EndChild();

		ImGui::PopStyleColor();

		
		ImGui::End();


	}

	


}