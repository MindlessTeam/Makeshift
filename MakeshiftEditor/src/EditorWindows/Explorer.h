// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <filesystem>

namespace MakeshiftEditor
{

	struct Explorer
	{

	public:
		Explorer();

	public:
		void renderIMGUI();

	private:
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_RootDirectory;

	};

}