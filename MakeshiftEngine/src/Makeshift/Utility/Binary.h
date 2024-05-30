// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace Makeshift
{
	namespace Util
	{

		// Binary
		// --------------------------------------------
		// Utilities for various Binary Operations
		struct Binary
		{

			//TODO: Implement Base64 En- and Decoding (Could be useful for Texture Data storage)
			// UNIMPLEMENTED!!!
			static std::string encodeBase64(const std::vector<unsigned char>& data);
			// UNIMPLEMENTED!!!
			static std::vector<unsigned char> decodeBase64(const std::string& data);

		};

	}
}