// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "TextureCreator.h"

#include <Makeshift/Core/Engine.h>

#include <Makeshift/Debug/Log.h>
#include <Makeshift/Version.h>

#include <json/json.h>

#include <Makeshift/OpenGL/Texture.h>
#include <Makeshift/Resource/Resources/Texture.h>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <iostream>
#include <fstream>

#include "Utility/Explorer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace MakeshiftEditor
{

	void TextureCreator::renderIMGUI()
	{

		if (!enabled) return;

		ImGui::Begin("Texture Creator", &enabled);

		ImGui::InputTextWithHint("Source Location:", "The location of your original image file", &m_TextureOrigin);
		if (ImGui::BeginDragDropTarget())
		{
			if (const auto payload = ImGui::AcceptDragDropPayload("EXTERNAL"))
			{
				const char* path = static_cast<const char*>(payload->Data);
				m_TextureOrigin = path;
			}
				//TODO: Accept File Browser thingies

			ImGui::EndDragDropTarget();
		}

		ImGui::InputTextWithHint("Target Location:", "The location of your 'compiled' image file", &m_TextureDestination);
		if (ImGui::BeginDragDropTarget())
		{
			if (const auto payload = ImGui::AcceptDragDropPayload("EXTERNAL"))
			{
				const char* path = static_cast<const char*>(payload->Data);
				m_TextureDestination = path;
			}
			if (const auto payload = ImGui::AcceptDragDropPayload("FILE_PATH"))
			{
				const char* path = static_cast<const char*>(payload->Data);
				m_TextureDestination = path;
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::SameLine();
		if(ImGui::Button("Browse"))
		{
			m_TextureDestination = Util::Explorer::getFilePath();
		}

		if (ImGui::Button("Compile Texture", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
		{

			m_AvailableTexture = false;

			if (m_TextureOrigin.empty() || m_TextureDestination.empty())
			{
				ImGui::End();
				return;
			}

			m_ImageData.clear();
			m_ImageHeight = 0;
			m_ImageWidth = 0;

			int channels;
			unsigned char* imageData = stbi_load(m_TextureOrigin.c_str(), &m_ImageWidth, &m_ImageHeight, &channels, STBI_rgb);

			for (int i = 0; i < m_ImageWidth * m_ImageHeight * 3; i++)
			{
				m_ImageData.push_back(imageData[i]);
			}

			Json::Value root;
			
			root["Type"] = "Texture";
			root["Version"]["major"] = VERSION_MAJOR;
			root["Version"]["minor"] = VERSION_MINOR;
			root["Version"]["patch"] = VERSION_PATCH;

			Json::Value imageDataJSON;
			for (auto byte : m_ImageData)
			{
				imageDataJSON.append(byte);
			}

			root["Image Data"] = imageDataJSON;

			root["Width"] = m_ImageWidth;
			root["Height"] = m_ImageHeight;

			std::ofstream file(m_TextureDestination);
			file << root;
			file.close();

			m_Textures.push_back(Makeshift::Engine::getInstance().getResourceMap()->addResource<Makeshift::Texture>(m_TextureDestination));

		}


		for (auto texture : m_Textures)
		{
			ImGui::Text("%x x %x  |", texture->getData().width, texture->getData().height);
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%x", texture->getData().texture->getRenderID());
			ImGui::Image((ImTextureID)texture->getData().texture->getRenderID(), ImVec2(64, 64));
			ImGui::Separator();
		}
		
		ImGui::End();

	}

}
