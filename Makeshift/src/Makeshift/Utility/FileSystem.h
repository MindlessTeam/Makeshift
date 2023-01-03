// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace Makeshift
{

	namespace Util
	{

		// File Locations
		// --------------------------------------------
		// Utility to quickly retrieve paths.
		struct FileLocations
		{

			static std::string& contentLocation();
			static std::string& modelLocation();

			static std::string& logLocation();

		};

		// File System
		// --------------------------------------------
		// Utility for various file-system I/O interactions.
		struct FileSystem
		{

			static bool dirExist(const std::string& path);
			static std::string loadRawText(const std::string& path);

		public: // Loading

		public: // Saving

		};

	}
}