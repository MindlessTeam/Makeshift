// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Random.h"

#include "Makeshift/Debug/Log.h"

#include <random>
#include <limits>

namespace Makeshift
{
	namespace Util
	{

		static std::random_device device;
		static std::mt19937 generator{device()};

		int Random::generateRandomInt()
		{
			DEBUG_TRACE("Makeshift::Util::Random::generateRandomInt()");

			static std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);
			return distribution(device);

		}

		int Random::generateRandomIntRange(int min, int max)
		{
			DEBUG_TRACE("Makeshift::Util::Random::generateRandomIntRange()");

			static std::uniform_int_distribution<int> distribution(min, max);
			return distribution(device);

		}

	}
}