// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

#include <Makeshift/Resource/Resources/Texture.h>
#include "ContentMeta.h"

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

	private:
		std::shared_ptr<Makeshift::Texture> m_FolderIcon;
		std::shared_ptr<Makeshift::Texture> m_FileIcon;
		std::shared_ptr<Makeshift::Texture> m_ResourceIcon;

		std::shared_ptr<ContentMeta> m_ContentMeta;

	private:
		void cleanUpMeta();
		void saveContentMeta();

	};

}