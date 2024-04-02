// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{
	namespace Util
	{

		// Random
		// -----------------------------------------
		// Utility for generating random numbers.
		struct Random
		{

			// Random::generateRandomInt()
			// -------------------------------------
			// Generates a random int in the range
			// of INT_MIN and INT_MAX.
			static int generateRandomInt();
			
			// Random::generateRandomIntRange()
			// -------------------------------------
			// Generates a random int in the range
			// of min and max.
			static int generateRandomIntRange(int min, int max);

		};

	}
}