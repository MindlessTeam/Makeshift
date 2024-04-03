// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

#include <unordered_map>

#include <Makeshift/Resource/Resources/Texture.h>
#include "ContentMeta.h"

#include <imgui/imgui.h>

namespace MakeshiftEditor
{

	// File Browser
	// ---------------------------------------------
	// Editor window for browsing the project folder.
	//NOTE: Currently the "project folder" is always "content\\"
	struct FileBrowser
	{

		bool enabled = false;

		void renderIMGUI();

	public:
		~FileBrowser();

	private: // Values
		std::string currentPath = "content\\";
		std::string selectedFile;

	private:
		int cellSize = 128;

		bool showDirectories = true;
		bool showFiles = true;

		std::unordered_map<std::string, bool> filters;

		bool isToolTipOpen = false;
		ImVec2 cursorToolTipOrigin;

		float toolTipOpenTime = 0;

	private:
		std::shared_ptr<Makeshift::Texture> m_FolderIcon;
		std::shared_ptr<Makeshift::Texture> m_FileIcon;
		std::shared_ptr<Makeshift::Texture> m_ResourceIcon;

		std::shared_ptr<ContentMeta> m_ContentMeta;

	private:
		void renderItemsInDirectory(const std::string& path);

	private:
		void cleanUpMeta();
		void saveContentMeta();

	};

}