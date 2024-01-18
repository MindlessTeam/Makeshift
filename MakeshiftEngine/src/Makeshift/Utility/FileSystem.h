// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Makeshift/Makeshift.hpp"
#include "Makeshift/Debug/Log.h"

#include <string>
#include <fstream>
#include <sstream>
#include <strstream>

namespace Makeshift
{

	struct FileLocations
	{

		static std::string contentLocation();
		static std::string saveGameLocation();
		static std::string modelLocation(bool savegame);
		static std::string materialLocation(bool savegame);
		static std::string levelLocation(bool savegame);
		static std::string fontLocation();
		static std::string logLocation();

	};

	struct FileSystem
	{

		static void initFileSystem();
		static void initSaveGame();

		static bool dirExist(const std::string& path);
		static bool makeDir(const std::string& path);
		static bool makeDirComplete(const std::string& path);

	};

}