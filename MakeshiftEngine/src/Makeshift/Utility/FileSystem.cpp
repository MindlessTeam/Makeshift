// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "FileSystem.h"

#include "Makeshift/Debug/Log.h"

#include <fstream>
#include <sstream>
#include <strstream>

#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <glm/gtx/hash.hpp>

namespace Makeshift
{
	namespace Util
	{

		std::string& FileLocations::contentLocation()
		{
			static std::string cLoc = "content";
			return cLoc;
		}

		std::string& FileLocations::modelLocation()
		{
			static std::string mLoc = "content/mdl";
			return mLoc;
		}

		std::string& FileLocations::logLocation()
		{
			static std::string lLoc = "log";
			return lLoc;
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

		std::string FileSystem::loadRawText(const std::string& path)
		{
			DEBUG_TRACE("Makeshift::Util::FileSystem::loadRawText()");

			DEBUG_INFO("Loading file '{}'...", path);
			std::ifstream input(path, std::ios::in | std::ios::binary);
			if (input)
			{
				std::string content;

				input.seekg(0, std::ios::end);
				content.resize(input.tellg());
				input.seekg(0, std::ios::beg);
				input.read(&content[0], content.size());
				input.close();

				return(content);
			}

			DEBUG_ERROR("Failed to load '{}'!", path);

		}

	}