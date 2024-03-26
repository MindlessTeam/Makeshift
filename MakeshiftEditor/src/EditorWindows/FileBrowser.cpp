// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "FileBrowser.h"

#include "Utility/Util.h"

#include <Makeshift/Makeshift.hpp>

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <fstream>

#include <filesystem>

namespace MakeshiftEditor
{


	void FileBrowser::renderIMGUI()
	{

		if (!enabled)
			return;

		if(!m_ResourceIcon)
			m_ResourceIcon = Makeshift::Engine::getInstance().getResourceMap()->addResource<Makeshift::Texture>("content/editor/resource_icon.json");
		if(!m_FolderIcon)
			m_FolderIcon = Makeshift::Engine::getInstance().getResourceMap()->addResource<Makeshift::Texture>("content/editor/folder_icon.json");
		if(!m_FileIcon)
			m_FileIcon = Makeshift::Engine::getInstance().getResourceMap()->addResource<Makeshift::Texture>("content/editor/file_icon.json");

		if (!m_ContentMeta)
			m_ContentMeta = Makeshift::Engine::getInstance().getResourceMap()->addResource<ContentMeta>("meta.json");

		ImGui::Begin("File Browser", &enabled);

		ImGui::SliderInt("Cell Size:", &cellSize, 32, 256);

		int availableWidth = ImGui::GetContentRegionAvail().x;
		int cellsPerRow = availableWidth / (cellSize + (4 * Makeshift::ImGuiRenderer::getUISizeModifier()));


		int i = 0;
		for (const auto& entry : std::filesystem::directory_iterator(currentPath))
		{
			if (i < cellsPerRow && i != 0)
			{
				ImGui::SameLine();
			}
			ImGui::BeginChild(entry.path().string().c_str(), ImVec2(cellSize,cellSize + (Makeshift::ImGuiRenderer::getFontSize() * 2) + 4 * Makeshift::ImGuiRenderer::getUISizeModifier() * 2), false, ImGuiWindowFlags_NoScrollbar);

			std::string trimmedPath = Util::trimTextToFitArea(entry.path().string().c_str(), cellSize, true);

			if (entry.is_directory())
			{
				ImGui::Image((ImTextureID)m_FolderIcon->getData().texture->getRenderID(), ImVec2(cellSize, cellSize));
				ImGui::Text(trimmedPath.c_str());
			}
			else
			{
				if (entry.path().extension() == ".json")
				{
					ImGui::Image((ImTextureID)m_ResourceIcon->getData().texture->getRenderID(), ImVec2(cellSize, cellSize));
					ImGui::Text(trimmedPath.c_str());
					if (m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str()) == m_ContentMeta->getData().m_Resources.end())
						m_ContentMeta->addEntry(entry.path().string().c_str());
					ImGui::Text("%s | V %d . %d . %d ",
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.first.c_str(),
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.second.major,
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.second.minor,
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.second.patch);
				}
				else
				{
					ImGui::Image((ImTextureID)m_FileIcon->getData().texture->getRenderID(), ImVec2(cellSize, cellSize));
					ImGui::Text(trimmedPath.c_str());
				}
			}

			ImGui::EndChild();

			if (i >= cellsPerRow)
			{
				i = 1;
			}
			else
			{
				i++;
			}
			

		}

		ImGui::End();

	}

	void FileBrowser::cleanUpMeta()
	{

		for (auto resource : m_ContentMeta->getData().m_Resources)
		{
			if (!std::filesystem::exists(resource.first))
			{
				
				m_ContentMeta->getData().m_Resources.erase(resource.first);

			}

		}

	}

	void FileBrowser::saveContentMeta()
	{

		Json::Value root;

		root["Type"] = "ContentMeta";
		root["Version"]["major"] = VERSION_MAJOR;
		root["Version"]["minor"] = VERSION_MINOR;
		root["Version"]["patch"] = VERSION_PATCH;

		Json::Value resources;
		for (auto resource : m_ContentMeta->getData().m_Resources)
		{

			Json::Value resourceJSON;
			resourceJSON["Location"] = resource.first;
			resourceJSON["Type"] = resource.second.first;

			resourceJSON["Version"]["major"] = resource.second.second.major;
			resourceJSON["Version"]["minor"] = resource.second.second.minor;
			resourceJSON["Version"]["patch"] = resource.second.second.patch;

			resources.append(resourceJSON);

		}

		root["Resources"] = resources;

		std::ofstream file("meta.json");
		file << root;
		file.close();

	}

	FileBrowser::~FileBrowser()
	{
		

		if (m_ResourceIcon)
			Makeshift::Engine::getInstance().getResourceMap()->removeResource(m_ResourceIcon->m_Location);
		if (m_FolderIcon)
			Makeshift::Engine::getInstance().getResourceMap()->removeResource(m_FolderIcon->m_Location);
		if (m_FileIcon)
			Makeshift::Engine::getInstance().getResourceMap()->removeResource(m_FileIcon->m_Location);
		if (m_ContentMeta)
		{
			Makeshift::Engine::getInstance().getResourceMap()->removeResource(m_ContentMeta->m_Location);
			cleanUpMeta();
			saveContentMeta();
		}
	}

}
