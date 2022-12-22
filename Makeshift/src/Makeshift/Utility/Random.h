// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{
	namespace Util
	{

		struct Random
		{

			static int generateRandomInt();
			static int generateRandomIntRange(int min, int max);

		};

	}
}