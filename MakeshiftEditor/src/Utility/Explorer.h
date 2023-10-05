// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace MakeshiftEditor
{

	struct Explorer
	{

		static std::string getFilePath();
		static std::string getRelativeFilePath();

		static std::string getCreatedFilePath();
		static std::string getRelativeCreatedFilePath();

		static std::string getFolderPath();
		static std::string getRelativeFolderPath();

	};

}