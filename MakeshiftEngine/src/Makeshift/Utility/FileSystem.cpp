// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "FileSystem.h"

#include <string>
#include <fstream>
#include <sstream>
#include <strstream>

#include <sys/stat.h>
#include <sys/types.h>

namespace Makeshift
{

	std::string FileLocations::contentLocation()
	{
		return "content/";
	}

	std::string FileLocations::saveGameLocation()
	{
		return "savegames/savegame" + Engine::getInstance().getCurrentSaveGame() + (std::string)"/";
	}

	std::string FileLocations::quickSaveLocation()
	{
		return "savegames/quick/";
	}

	std::string FileLocations::modelLocation(bool savegame)
	{
		if (savegame)
			return saveGameLocation() + "mdl/";

		return contentLocation() + "mdl/";
	}

	std::string FileLocations::materialLocation(bool savegame)
	{
		if (savegame)
			return saveGameLocation() + "mat/";

		return contentLocation() + "mat/";
	}

	std::string FileLocations::levelLocation(bool savegame)
	{
		if (savegame)
			return saveGameLocation() + "lvl/";

		return contentLocation() + "lvl/";
	}

	std::string FileLocations::fontLocation()
	{
		return contentLocation() + "font/";
	}

	std::string FileLocations::logLocation()
	{
		return "log";
	}


	void FileSystem::initFileSystem()
	{

		if (!dirExist(FileLocations::contentLocation()))
		{
			makeDirComplete(FileLocations::contentLocation());
		}
		if (!dirExist(FileLocations::quickSaveLocation()))
		{
			makeDirComplete(FileLocations::quickSaveLocation());
		}
		if (!dirExist(FileLocations::modelLocation(false)))
		{
			makeDirComplete(FileLocations::modelLocation(false));
		}
		if (!dirExist(FileLocations::materialLocation(false)))
		{
			makeDirComplete(FileLocations::materialLocation(false));
		}
		if (!dirExist(FileLocations::levelLocation(false)))
		{
			makeDirComplete(FileLocations::levelLocation(false));
		}

	}

	void FileSystem::initSaveGame()
	{

		if (!dirExist(FileLocations::saveGameLocation()))
		{
			makeDirComplete(FileLocations::saveGameLocation());
		}
		if (!dirExist(FileLocations::modelLocation(true)))
		{
			makeDirComplete(FileLocations::modelLocation(true));
		}
		if (!dirExist(FileLocations::materialLocation(true)))
		{
			makeDirComplete(FileLocations::materialLocation(true));
		}
		if (!dirExist(FileLocations::levelLocation(true)))
		{
			makeDirComplete(FileLocations::levelLocation(true));
		}

	}

	// See StackOverflow:
	// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
	bool FileSystem::dirExist(const std::string& path)
	{
		DEBUG_TRACE("Makeshift::Util::FileSystem::dirExist()");

		DEBUG_INFO("Checking if directory '{}' exists...", path);
		struct stat buffer;
		return(stat(path.c_str(), &buffer) == 0);
	}

	bool FileSystem::makeDir(const std::string& path)
	{
		DEBUG_TRACE("Makeshift::FileSystem::makeDir()");

		DEBUG_INFO("Creating directory '{}'...", path);

		if (mkdir(path.c_str()) == 0) 
		{
			return true;
		}
		else 
		{
			DEBUG_ERROR("Failed to create directory '{}'", path);
			return false;
		}
	}

	bool FileSystem::makeDirComplete(const std::string& path) 
	{
		DEBUG_TRACE("Makeshift::FileSystem::makeDirComplete()");

		DEBUG_INFO("Creating directory '{}' with parent directories...", path);

		std::string dirPath = path;

		for (size_t i = 0; i < dirPath.size(); i++) 
		{
			if (dirPath[i] == '/' || dirPath[i] == '\\') 
			{
				char temp = dirPath[i];
				dirPath[i] = '\0';

				// Try creating the directory
				if (mkdir(dirPath.c_str()) != 0) 
				{
					if (errno != EEXIST) 
					{
						DEBUG_ERROR("Failed to create directory '{}'", dirPath);
						return false;
					}
				}

				// Restore the separator
				dirPath[i] = temp;
			}
		}

		if (mkdir(dirPath.c_str()) != 0) 
		{
			DEBUG_ERROR("Failed to create directory '{]'", dirPath);
			return false;
		}

		return true;
	}

}