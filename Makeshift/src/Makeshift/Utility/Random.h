// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{
	namespace Util
	{

		// Random
		// --------------------------------------------
		// Utility for generating random numbers.
		struct Random
		{

			static int generateRandomInt();
			static int generateRandomIntRange(int min, int max);

		};

	}
}