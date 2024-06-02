// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "TextureEditor.h"

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include <Makeshift/Resource/Resources/Texture.h>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <imgui/imgui_internal.h>

#include <codecvt>
#include <locale>

#include <IconsMaterialSymbols.h>

#include "Utility/Util.h"
#include "Utility/Explorer.h"
#include "Utility/DragDropTypes.h"

#include "UI/Elements.h"
#include "UI/Style.h"

#include <Makeshift/Core/Time.h>
#include <Makeshift/Utility/Vector.h>

#include <Makeshift/Debug/Log.h>

#include <iostream>
#include <fstream>

namespace MakeshiftEditor
{

	void TextureEditor::renderIMGUI()
	{
		DEBUG_TRACE("MakeshiftEditor::TextureEditor::renderIMGUI()");

		if (!m_Enabled)
			return;

		ImGui::SetNextWindowSize(ImVec2(750, 500), ImGuiCond_FirstUseEver);
		ImGui::Begin("Texture Editor", &m_Enabled);

		renderMenuBar();
		renderViewSettings();
		if (m_ShowTextureSettings)
		{
			renderTextureSettings();
		}
		renderTexturePreview();
		renderFileInfoOverlay();

		//if (Elements::BeginDragDropTargetWindow())
		//{
		//
		//	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(MAKESHIFT_PAYLOAD_RESOURCE)) 
		//	{
		//	}
		//	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(MAKESHIFT_PAYLOAD_EXTERNAL))
		//	{
		//	}
		//	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(MAKESHIFT_PAYLOAD_FILEPATH))
		//	{
		//	}
		//
		//	ImGui::EndDragDropTarget();
		//}


		ImGui::End();

	}

	void TextureEditor::renderMenuBar()
	{
		DEBUG_TRACE("MakeshiftEditor::TextureEditor::renderMenuBar()");

		ImGui::PushStyleColor(ImGuiCol_ChildBg, Style::LightAccent());
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
		ImGui::BeginChild("MenuBar", ImVec2(ImGui::GetContentRegionAvail().x, Util::getRequiredVerticalTextSize(1, true)));

		ImGui::Button(ICON_MS_ADD "New");

		ImGui::SameLine(0, 2);
		ImGui::Button(ICON_MS_IMAGE_SEARCH "Import");

		ImGui::SameLine(0, 2);
		ImGui::Button(ICON_MS_SEND_MONEY "Compile");

		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

	}

	void TextureEditor::renderViewSettings()
	{
		DEBUG_TRACE("MakeshiftEditor::TextureEditor::renderViewSettings()");

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
		ImGui::BeginChild("ViewSettings", ImVec2(Util::getRequiredVerticalTextSize(1, true), ImGui::GetContentRegionAvail().y));

		if(ImGui::Button(ICON_MS_EDIT))
		{
			m_ShowTextureSettings = !m_ShowTextureSettings;
		}
		Elements::ToolTip("Show Texture Settings");

		ImGui::Separator();

		ImGui::Button(ICON_MS_STACKS);
			Elements::ToolTip("Show All Channels");

		ImGui::Button(ICON_MS_LOOKS_ONE);
			Elements::ToolTip("Show Channel 1");

		ImGui::Button(ICON_MS_LOOKS_TWO);
			Elements::ToolTip("Show Channel 2");

		ImGui::Button(ICON_MS_LOOKS_3);
			Elements::ToolTip("Show Channel 3");

		ImGui::Button(ICON_MS_TEXTURE);
			Elements::ToolTip("Show Alpha Channel");

		ImGui::EndChild();
		ImGui::PopStyleVar();

	}

	void TextureEditor::renderTextureSettings()
	{
		DEBUG_TRACE("MakeshiftEditor::TextureEditor::renderTextureSettings()");

		ImGui::SameLine();
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, Style::InternalWindowPadding());
		ImGui::BeginChild("TextureSettings", ImVec2(25,ImGui::GetContentRegionAvail().y), ImGuiChildFlags_ResizeX | ImGuiChildFlags_AlwaysUseWindowPadding);
		
		Elements::CenteredText("Texture Settings");

		ImGui::NewLine();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, Style::DarkAccent());

		if (ImGui::BeginChild("##GeneralSettings", ImVec2(ImGui::GetContentRegionAvail().x,0), ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AutoResizeY))
		{

			Elements::CenteredText(ICON_MS_LINE_START "General" ICON_MS_LINE_END);

			ImGui::NewLine();

			ImGui::Text(ICON_MS_BLUR_ON "Filtering: ");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
			if (ImGui::BeginCombo("##TextureFiltering", "-- Select --"))
			{
				ImGui::EndCombo();
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + Style::ItemSpacing());

			ImGui::Text(ICON_MS_BORDER_STYLE "Wrapping: ");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
			if (ImGui::BeginCombo("##TextureWrapping", "-- Select --"))
			{
				ImGui::EndCombo();
			}

		}
		ImGui::EndChild();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + Style::ItemSpacingWide());

		if (ImGui::BeginChild("##Orientation", ImVec2(ImGui::GetContentRegionAvail().x, 0), ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AutoResizeY))
		{

			Elements::CenteredText(ICON_MS_LINE_START "Orientation" ICON_MS_LINE_END);

			ImGui::NewLine();

			ImGui::Button(ICON_MS_ROTATE_90_DEGREES_CW, ImVec2(ImGui::GetContentRegionAvail().x / 2, 0));
				Elements::ToolTip("Rotate 90 Degrees Clockwise");

			ImGui::SameLine();
			ImGui::Button(ICON_MS_ROTATE_90_DEGREES_CCW, ImVec2(ImGui::GetContentRegionAvail().x, 0));
				Elements::ToolTip("Rotate 90 Degrees Counter-Clockwise");

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + Style::ItemSpacing());

			ImGui::Button(ICON_MS_FLIP "Flip", ImVec2(ImGui::GetContentRegionAvail().x, 0));

		}
		ImGui::EndChild();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + Style::ItemSpacingWide());

		if (ImGui::BeginChild("##Crop", ImVec2(ImGui::GetContentRegionAvail().x, 0), ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AutoResizeY))
		{

			Elements::CenteredText(ICON_MS_LINE_START "Crop" ICON_MS_LINE_END);

			ImGui::NewLine();

			ImGui::Text(ICON_MS_CROP "Crop Mode: ");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
			if (ImGui::BeginCombo("##CropMode", "-- Select --"))
			{
				ImGui::EndCombo();
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + Style::ItemSpacing());

			ImGui::Button(ICON_MS_CROP_FREE "Crop", ImVec2(ImGui::GetContentRegionAvail().x, 0));

		}
		ImGui::EndChild();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + Style::ItemSpacingWide());

		if (ImGui::BeginChild("##Size", ImVec2(ImGui::GetContentRegionAvail().x, 0), ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AutoResizeY))
		{

			Elements::CenteredText(ICON_MS_LINE_START "Size" ICON_MS_LINE_END);

			ImGui::NewLine();

			ImGui::Text(ICON_MS_WIDTH "Clamp Width: ");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
			if (ImGui::BeginCombo("##ClampWidth", "-- Select --"))
			{
				ImGui::EndCombo();
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + Style::ItemSpacing());

			ImGui::Text(ICON_MS_HEIGHT "Clamp Height: ");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
			if (ImGui::BeginCombo("##Clampheight", "-- Select --"))
			{
				ImGui::EndCombo();
			}

		}
		ImGui::EndChild();

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor();

		Elements::Border(1.0f, ImGuiDir_Right);

		ImGui::EndChild();
		ImGui::PopStyleVar(2);		

	}

	void TextureEditor::renderTexturePreview()
	{
		DEBUG_TRACE("MakeshiftEditor::TextureEditor::renderTexturePreview()");

		ImGui::PushStyleColor(ImGuiCol_ChildBg, Style::LighterAccent());
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);

		ImGui::SameLine();
		ImGui::BeginChild("TexturePreview", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

		//ImGui::Button("Texture Preview", ImGui::GetContentRegionAvail());

		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();

	}

	void TextureEditor::renderFileInfoOverlay()
	{
		DEBUG_TRACE("MakeshiftEditor::TextureEditor::renderFileInfoOverlay()");

		ImVec2 originPos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x - 200 * Makeshift::ImGuiRenderer::getUISizeModifier() - 5, ImGui::GetWindowPos().y + Util::getRequiredVerticalTextSize(2, true) + 7);

		ImGui::PushStyleColor(ImGuiCol_ChildBg, Style::DarkOverlay());

		ImGui::SetCursorScreenPos(originPos);
		ImGui::BeginChild("TestDisplay", ImVec2(200 * Makeshift::ImGuiRenderer::getUISizeModifier(), 135 * Makeshift::ImGuiRenderer::getUISizeModifier()), ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY);

		ImGui::NewLine();
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, Style::InternalWindowPaddingAxis()));
		
		Elements::CenteredText(ICON_MS_LINE_START "File Info" ICON_MS_LINE_END);

		ImGui::Indent(Style::HeaderIndent());
		ImGui::Text(ICON_MS_DESCRIPTION "Location: $val");
		ImGui::Text(ICON_MS_HARD_DRIVE "Size: $val");
		ImGui::Text(ICON_MS_STRAIGHTEN "Width: $val , Height: $val");

		ImGui::Unindent();

		ImGui::PopStyleVar();

		ImGui::EndChild();

		ImGui::PopStyleColor();

	}

	void TextureEditor::loadPNG()
	{
		
		m_TextureData.clear();
		m_TextureData = Makeshift::Texture::loadImageData(m_SourceLocation, m_Width, m_Height, m_TextureFormat);

		Makeshift::Texture::splitImageDataIntoChannels(m_TextureData, m_TextureFormat, m_RedData, m_GreenData, m_BlueData, m_AlphaData);

		m_Texture.reset();
		m_Texture = std::make_shared<Makeshift::OpenGL::Texture>(m_TextureData.data(), m_Width, m_Height, m_TextureFormat);
		m_ChannelR.reset();
		m_ChannelR = std::make_shared<Makeshift::OpenGL::Texture>(m_RedData.data(), m_Width, m_Height, Makeshift::OpenGL::Texture::TextureFormat::SINGLE_CHANNEL);
		
		if (m_TextureFormat != Makeshift::OpenGL::Texture::SINGLE_CHANNEL)
		{
			m_ChannelG.reset();
			m_ChannelG = std::make_shared<Makeshift::OpenGL::Texture>(m_GreenData.data(), m_Width, m_Height, Makeshift::OpenGL::Texture::TextureFormat::SINGLE_CHANNEL);
			m_ChannelB.reset();
			m_ChannelB = std::make_shared<Makeshift::OpenGL::Texture>(m_BlueData.data(), m_Width, m_Height, Makeshift::OpenGL::Texture::TextureFormat::SINGLE_CHANNEL);
			if (m_TextureFormat == Makeshift::OpenGL::Texture::RGBA)
			{
				m_ChannelA.reset();
				m_ChannelA = std::make_shared<Makeshift::OpenGL::Texture>(m_AlphaData.data(), m_Width, m_Height, Makeshift::OpenGL::Texture::TextureFormat::SINGLE_CHANNEL);
			}
		}
		switch (m_TextureFormat)
		{
		case Makeshift::OpenGL::Texture::TextureFormat::SINGLE_CHANNEL:
			m_CurrentlySelectedTextureFormat = "Single Channel";
			break;
		case Makeshift::OpenGL::Texture::TextureFormat::RGB:
			m_CurrentlySelectedTextureFormat = "RGB";
			break;
		case Makeshift::OpenGL::Texture::TextureFormat::RGBA:
			m_CurrentlySelectedTextureFormat = "RGB + Alpha";
			break;
		}

		m_TextureFiltering = Makeshift::OpenGL::Texture::TextureFiltering::LINEAR;
		m_CurrentlySelectedTextureFilteringMode = "Linear";

		m_TextureWrapping = Makeshift::OpenGL::Texture::TextureWrapping::REPEAT;
		m_CurrentlySelectedTextureWrappingMode = "Repeat";

		m_ShowTextureChannel = 0;

	}

	void TextureEditor::loadResource()
	{

	}

	void TextureEditor::clearEditor()
	{

		m_CurrentlySelectedTextureFormat = "--Select--";
		m_CurrentlySelectedTextureFilteringMode = "--Select--";
		m_CurrentlySelectedTextureWrappingMode = "--Select--";
		m_CurrentlySelectedCropMode = "--Select--";
		m_CurrentlySelectedWidth = "--Select--";
		m_CurrentlySelectedHeight = "--Select--";

		m_Texture.reset();
		m_TextureData.clear();

		m_ChannelR.reset();
		m_RedData.clear();

		m_ChannelG.reset();
		m_GreenData.clear();

		m_ChannelB.reset();
		m_BlueData.clear();

		m_ChannelA.reset();
		m_AlphaData.clear();

	}

	


}