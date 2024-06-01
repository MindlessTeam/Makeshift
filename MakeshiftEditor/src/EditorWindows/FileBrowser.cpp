// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "FileBrowser.h"

#include "Utility/Util.h"

#include <Makeshift/Makeshift.hpp>

#include <Makeshift/Graphics/ImGuiRenderer.h>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <fstream>

#include <filesystem>

namespace MakeshiftEditor
{


	void FileBrowser::renderIMGUI()
	{
		DEBUG_TRACE("MakeshiftEditor::FileBrowser::renderIMGUI()");

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

		ImGui::SetNextWindowSizeConstraints(ImVec2(650,650), ImVec2(10000000,10000000));
		ImGui::Begin("File Browser", &enabled);

		// I don't like the way ImGui::Column() looks, so we're doing some simple
		// calculations to figure out where to place the items.
		int availableWidth = ImGui::GetContentRegionAvail().x;
		int cellsPerRow = availableWidth / (cellSize + (4 * Makeshift::ImGuiRenderer::getUISizeModifier()));

		ImVec2 windowOrigin = ImGui::GetCursorPos(); // Used as a 0,0 for the window
		
		float itemRounding = 4 * Makeshift::ImGuiRenderer::getUISizeModifier();

		// Make a bit of space for the settings bar to go.
		ImGui::SetCursorPos(ImVec2(windowOrigin.x, windowOrigin.y + Util::getRequiredVerticalTextSize(1) + (4 * Makeshift::ImGuiRenderer::getUISizeModifier())));
		ImGui::BeginChild("ContentArea", ImVec2(ImGui::GetContentRegionAvail().x, 0));

		// A bit of styling
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, itemRounding);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImVec4(1.00f, 1.00f, 1.00f, 0.14f)));
		
		// Reused values to clean up the code a bit
		ImVec2 itemSize = ImVec2(cellSize, cellSize + Util::getRequiredVerticalTextSize(2));

		int i = 0; // To Keep Track where in the column we are
		for (const auto& entry : std::filesystem::directory_iterator(currentPath))
		{

			// Apply filters
			if (entry.is_directory() && !showDirectories)
				continue;

			if (!entry.is_directory() && entry.path().extension() != ".json" && !showFiles)
				continue;

			if (entry.path().extension() == ".json")
			{
				if (m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str()) == m_ContentMeta->getData().m_Resources.end())
					m_ContentMeta->addEntry(entry.path().string().c_str());

				// This code looks a bit confusing, but it essentially just
				// checks whether the current item is included in the filters
				// and if it isn't ignores it.

				bool marked = false;
				for (auto filter : filters)
				{
					marked = true;
					if (m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.first == filter.first && filter.second == false)
					{
						marked = true;
						break;
					}
					else
					{
						marked = false;
					}
				}

				if (marked)
					continue;
			}

			// We start the iteration process at 1.
			// This is so for the first line no "ImGui::SameLine()" is called. For 
			// whatever reason using "ImGui::NextLine()" before this loop (which was
			// my original plan) adds an annoying bit of padding to the first row.
			// This way ImGui just does it's normal padding calculations.
			// It's a bit hacky but it works.
			if (i < cellsPerRow && i != 0)
			{
				// As Long as there is space in the area, we add
				// another item.
				ImGui::SameLine();
			}

			ImGui::BeginChild(entry.path().string().c_str(), itemSize, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

			ImVec2 itemOrigin = ImGui::GetCursorPos(); // Used as a 0,0 for the current item

			std::string trimmedPath = Util::trimTextToFitArea(entry.path().string().c_str(), cellSize, true);

			if (entry.is_directory())
			{
				// Show Folder Icon and the path
				ImGui::Image((ImTextureID)m_FolderIcon->getData().texture->getRenderID(), ImVec2(cellSize, cellSize));
				ImGui::Text(trimmedPath.c_str());

				if (ImGui::IsWindowHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					// Go into the folder
					currentPath = entry.path().string();
				}
			}
			else
			{
				if (entry.path().extension() == ".json")
				{
					// The item is... presumably a resource (should probably add a
					// check for that but oh well). We display the resource icon
					// it's path and meta info.
					ImGui::Image((ImTextureID)m_ResourceIcon->getData().texture->getRenderID(), ImVec2(cellSize, cellSize));
					ImGui::Text(trimmedPath.c_str());

					// Make sure the resource is available in the content meta before
					// reading the data from it.
					if (m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str()) == m_ContentMeta->getData().m_Resources.end())
						m_ContentMeta->addEntry(entry.path().string().c_str());
					ImGui::Text("%s | V. %d . %d . %d ",
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.first.c_str(),
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.second.major,
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.second.minor,
						m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.second.patch);

					if (filters.find(m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.first) == filters.end())
					{
						filters.emplace(m_ContentMeta->getData().m_Resources.find(entry.path().string().c_str())->second.first, true);
					}
				}
				else
				{
					// Anything else will just get the file icon.
					// Maybe in the future we'll add a couple more icons...
					ImGui::Image((ImTextureID)m_FileIcon->getData().texture->getRenderID(), ImVec2(cellSize, cellSize));
					ImGui::Text(trimmedPath.c_str());
				}
			}


			if (ImGui::IsWindowHovered() && cellSize > 0) // Redundant check?
			{
				// Place a semi-transparent dark rect over the current item
				// to indicate that the item is hovered.
				ImGui::GetWindowDrawList()->AddRectFilled(
					ImGui::GetWindowPos(),
					ImVec2(ImGui::GetWindowPos().x + cellSize, ImGui::GetWindowPos().y + itemSize.y),
					IM_COL32(0, 0, 0, 75),
					5,0
				);
				
			}

			// For some reason ImGui doesn't query child windows
			// at all when it comes to IDs. They do have them, but
			// they are pretty much ignored for anything other than
			// rendering as far as I can tell.
			// For this reason we create a dummy object over the entire
			// Item which IS queried.
			ImGui::SetCursorPos(itemOrigin);
			ImGui::Dummy(itemSize);

			// A dummy doesn't have an ID however (I guess I could push
			// one but I don't need to) which is why we use 
			// ImGuiDragDropFlags_SourceAllowNullID. Basically, ImGui does
			// all the work for us! :D
			if(ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				if (entry.path().extension() == ".json")
				{
					//PERHAPS: Don't allow dragging of "Corrupt" files.
					ImGui::SetDragDropPayload("MAKESHIFT_RESOURCE", entry.path().string().c_str(), entry.path().string().size() + 1);
					ImGui::Text("Resource: %s", entry.path().string().c_str());
				}
				else
				{
					ImGui::SetDragDropPayload("FILE_PATH", entry.path().string().c_str(), entry.path().string().size() + 1);
					ImGui::Text("Path: %s", entry.path().string().c_str());
				}
				ImGui::EndDragDropSource();
			}

			ImGui::EndChild(); // File
			

			if (i >= cellsPerRow)
			{
				// Start the next row
				i = 1;
			}
			else
			{
				i++;
			}
		}
		ImGui::PopStyleVar(); // Child Rounding
		ImGui::PopStyleColor(); // Child Background

		ImGui::EndChild();

		ImGui::SetCursorPos(ImVec2(windowOrigin.x, windowOrigin.y + ImGui::GetScrollY()));
		ImGui::BeginChild("SettingsBar", ImVec2(ImGui::GetContentRegionAvail().x, Util::getRequiredVerticalTextSize(1)));
		
		ImVec2 settingsBarOrigin = ImGui::GetCursorPos();

		// As soon as we are in a subfolder of content "enable"
		// the button.
		if (currentPath != "content" && currentPath != "content\\") // Perhaps make it absolute?
		{
			if (ImGui::Button("< ##ReturnToPrevious", ImVec2(Util::getRequiredVerticalTextSize(1), Util::getRequiredVerticalTextSize(1))))
			{
				currentPath = std::filesystem::path(currentPath).parent_path().string();
			}
		}
		else
		{
			ImGui::BeginDisabled(true);
			ImGui::Button("< ##ReturnToPrevious", ImVec2(Util::getRequiredVerticalTextSize(1), Util::getRequiredVerticalTextSize(1)));
			ImGui::EndDisabled();
		}

		float textSize = 150 * Makeshift::ImGuiRenderer::getUISizeModifier();

		// Everything is in one line.
		ImGui::SameLine();
		ImGui::Text(Util::trimTextToFitArea(currentPath, textSize, true).c_str());
		
		float sliderSize = ImGui::GetWindowWidth() - (2 * Util::getRequiredVerticalTextSize(1) + textSize + 4 * Makeshift::ImGuiRenderer::getUISizeModifier());

		ImGui::SameLine();
		// Since text doesn't allow a specific size to be set
		// we manually advance to the position that the text 
		// can (due to the trimming) have at its max length.
		ImGui::SetCursorPosX(settingsBarOrigin.x + Util::getRequiredVerticalTextSize(1) + textSize);
		ImGui::SetNextItemWidth(sliderSize);
		ImGui::SliderInt("##CellSize", &cellSize, 64, 256);
	
		ImGui::SameLine();
		if (ImGui::Button("Filters", ImVec2(Util::getRequiredVerticalTextSize(1), 0)))
		{
			isToolTipOpen = true;
			cursorToolTipOrigin = ImGui::GetMousePos();
		}

		ImGui::EndChild(); // Settings Bar

		ImGui::End(); //-------------- FILE BROWSER

		
	
		if (!isToolTipOpen)
			return;

		// ImGui does provide tooltip functionality, but this
		// is more of a right-click context menu with
		// interaction and items which wouldn't work with
		// ImGuis tooltip system.

		// Style the window to look like a popup.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(1, 1, 1, 1));

		ImGui::SetNextWindowPos(cursorToolTipOrigin);
		ImGui::Begin("##FileBrowserToolTip", &isToolTipOpen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::PopStyleVar(); // Window Rounding
		ImGui::PopStyleColor(); // Border shadow

		// Close the popup if the user clicks anywhere else
		// or it has not been hovered for a while.
		if (!ImGui::IsWindowHovered())
		{
			// We wait for half a second before closing the window.
			// From my (frankly very limited) testing I've found
			// that this is a nice balance. Shorter timespans can
			// sometimes close the window whilst you're still trying
			// to interact with it just because you moved outside for
			// a tiny moment. And longer periods get annoying because
			// IT JUST WON'T GO AWAY!!!!! (you get my point?)
			toolTipOpenTime += Makeshift::Time::getDeltaTime();

			if (toolTipOpenTime >= 0.5 || ImGui::IsMouseClicked(ImGuiMouseButton_Left) || ImGui::IsMouseClicked(ImGuiMouseButton_Middle) || ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				isToolTipOpen = false;
				toolTipOpenTime = 0;
			}
		}

		// Generic filters
		ImGui::Checkbox("Show Directories", &showDirectories);
		ImGui::Checkbox("Show Files", &showFiles);

		// Resource specific filters
		ImGui::Separator();
		ImGui::Text("Resources:");

		for (auto& filter : filters)
		{
			if (filter.first == "")
			{
				// Just so ImGui doesn't get a heart-attack with a null-id.
				ImGui::Checkbox("Unknown", &filter.second);
			}
			else
			{
				ImGui::Checkbox(filter.first.c_str(), &filter.second);
			}
		}
		
		ImGui::End(); //-------------- FILE BROWSER TOOL TIP

	}

	void FileBrowser::cleanUpMeta()
	{

		auto& resources = m_ContentMeta->getData().m_Resources;
		std::vector<std::string> keysToRemove;


		for (const auto& resource : resources)
		{
			if (!std::filesystem::exists(resource.first))
			{
				keysToRemove.push_back(resource.first);
			}
		}

		// We've got to do it this way because if we remove an entry whilst
		// looping through the map the iterator will just break and... BOOOOOOOOM!
		for (const auto& key : keysToRemove)
		{
			resources.erase(key);
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
