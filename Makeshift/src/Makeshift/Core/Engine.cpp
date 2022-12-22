// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Engine.h"

namespace Makeshift
{

	Engine* Engine::s_Instance = nullptr;

	void Engine::run()
	{

		if (s_Instance != nullptr)
			return;

		s_Instance;

		while (true)
		{

		}

	}

}