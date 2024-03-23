// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "FileBrowser.h"

#include <Makeshift/Makeshift.hpp>

#include <imgui/imgui.h>

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

		ImGui::Begin("File Browser", &enabled);

		

		ImGui::End();

	}

}
