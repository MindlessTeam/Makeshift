// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

#include <Makeshift/Resource/Resources/Texture.h>

namespace MakeshiftEditor
{

	struct FileBrowser
	{

		bool enabled = false;

		void renderIMGUI();

	private: // Values
		std::string currentPath = "content\\";
		std::string selectedFile;

	private:
		std::shared_ptr<Makeshift::Texture> m_FolderIcon;
		std::shared_ptr<Makeshift::Texture> m_FileIcon;
		std::shared_ptr<Makeshift::Texture> m_ResourceIcon;

	};

}