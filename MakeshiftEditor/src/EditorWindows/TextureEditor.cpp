// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "TextureEditor.h"

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <imgui/imgui_internal.h>

#include <codecvt>
#include <locale>

#include <IconsMaterialDesign.h>

#include "Utility/Util.h"
#include "Utility/Explorer.h"
#include <Makeshift/Core/Time.h>
#include <Makeshift/Utility/Vector.h>

#include <iostream>
#include <fstream>

namespace MakeshiftEditor
{

	void sleep()
	{
		_sleep(5000);
	}

	void TextureEditor::renderIMGUI()
	{

		// Once the creation has been flagged, we wait 0.2 seconds
		// before actually starting the operation. This is
		// just enough time for the IMGUI-popup to appear.
		// We do this to make sure the user is aware that something
		// is happening and doesn't force-close the engine. Afterall,
		// Texture-Compilation might take a while!
		if (m_FlagCreation)
		{
			m_TimeSinceFlag += Makeshift::Time::getDeltaTime();

			if (m_FlagCreation && m_TimeSinceFlag >= 0.2f)
			{
				sleep();
				m_FlagCreation = false;
				m_TimeSinceFlag = 0;
			}
		}	

		if (ImGui::BeginPopupModal("CompileTexturePopup", &m_FlagCreation, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("Compiling Texture...");

			ImGui::PushFont(Makeshift::ImGuiRenderer::getIconFont());

			ImGui::Text(ICON_MD_PENDING);

			ImGui::PopFont();

			ImGui::EndPopup();
		}

		if (!enabled)
			return;

		ImGui::SetNextWindowSize(ImVec2(500 * Makeshift::ImGuiRenderer::getUISizeModifier(), 440 * Makeshift::ImGuiRenderer::getUISizeModifier()), ImGuiCond_FirstUseEver);
		ImGui::Begin("Texture Editor", &enabled, ImGuiWindowFlags_MenuBar);

		//TODO: INPUT HANDLING!!!!!!!!
		if(ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Texture"))
			{
				if (ImGui::MenuItem("Open"));
				if (ImGui::MenuItem("Import", "Ctrl-I"))
				{
					m_PNGLocation = Explorer::getRelativeFilePath();
					// Load Texture!
				}
				if (ImGui::MenuItem("Save", "Ctrl-S"));
				if (ImGui::MenuItem("Save As...", "Ctrl-Shift-S"));
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Show Settings Pane", "Alt+S", m_ShowTextureSettings))
				{
					m_ShowTextureSettings = !m_ShowTextureSettings;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.05, 0.05f, 0.075f, 1.0f));

		// --- Quick Edit Buttons ---

		ImGui::BeginChild("Buttons", ImVec2(Util::getRequiredVerticalTextSize(1, true),ImGui::GetContentRegionAvail().y ));

		ImVec2 buttonSize = ImVec2(Util::getRequiredVerticalTextSize(1, true), Util::getRequiredVerticalTextSize(1, true));

		ImGui::PushFont(Makeshift::ImGuiRenderer::getIconFont());

		if (ImGui::Button(ICON_MD_ARROW_RIGHT))
		{
			m_ShowTextureSettings = !m_ShowTextureSettings;
		}
		ImGui::PopFont();

		ImGui::Separator();

		ImGui::BeginDisabled(!m_Texture);
		if (ImGui::Button("C", buttonSize))
		{
			m_TextureChannel = 0;
		}

		ImGui::EndDisabled();
		

		ImGui::EndChild();

		ImGui::SameLine();

		// --- Texture Settings ---

		if (m_ShowTextureSettings)
		{

			ImGui::BeginChild("Settings", ImVec2(150, ImGui::GetContentRegionAvail().y), ImGuiChildFlags_ResizeX);

			ImGui::EndChild();



			ImGui::SameLine();
		}

		// --- Texture Display ---

		ImGui::BeginChild("Texture Preview");

		if (!m_Texture)
		{
			float buttonSize = Util::getRequiredVerticalTextSize(1, true);
			ImVec2 areaSize = ImGui::GetContentRegionAvail();
			ImVec2 cursorPos;

			cursorPos.x = ImGui::GetCursorPosX() + areaSize.x / 2 - buttonSize / 2;
			cursorPos.y = ImGui::GetCursorPosY() + areaSize.y / 2 - buttonSize / 2;

			ImGui::SetCursorPos(cursorPos);
			ImGui::PushFont(Makeshift::ImGuiRenderer::getIconFont());

			ImGui::Button(ICON_MD_IMAGE_NOT_SUPPORTED);

			ImGui::PopFont();
		}
		else
		{
			ImVec2 areaSize = ImGui::GetContentRegionAvail();
			float maxImageDimensions = Makeshift::Util::Vector::getSmallestElement(glm::vec2(areaSize.x, areaSize.y));
			ImVec2 cursorPos;

			cursorPos.x = ImGui::GetCursorPosX() + areaSize.x / 2 - maxImageDimensions / 2;
			cursorPos.y = ImGui::GetCursorPosY() + areaSize.y / 2 - maxImageDimensions / 2;

			ImGui::SetCursorPos(cursorPos);			
			
			switch (m_TextureChannel)
			{
			case 0:
				ImGui::Image((ImTextureID)m_Texture->getRenderID(), ImVec2(maxImageDimensions, maxImageDimensions));
				break;
			case 1:
				if (m_ChannelR)
				{
					ImGui::Image((ImTextureID)m_ChannelR->getRenderID(), ImVec2(maxImageDimensions, maxImageDimensions));
				}
				break;
			case 2:
				if (m_ChannelG)
				{
					ImGui::Image((ImTextureID)m_ChannelG->getRenderID(), ImVec2(maxImageDimensions, maxImageDimensions));
				}				
				break;
			case 3:
				if (m_ChannelB)
				{
					ImGui::Image((ImTextureID)m_ChannelB->getRenderID(), ImVec2(maxImageDimensions, maxImageDimensions));
				}				
				break;
			case 4:
				if (m_ChannelA)
				{
					ImGui::Image((ImTextureID)m_ChannelA->getRenderID(), ImVec2(maxImageDimensions, maxImageDimensions));
				}				
				break;
			}
		}

		ImGui::EndChild();

		ImGui::PopStyleColor();

		
		ImGui::End();


	}

	


}