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

		s_Instance = this;

		// Initialize the pointers
		m_Display = new Display();

		// Begin Initialization
		m_Display->createDisplay();

		// Game Loop
		while (m_Display->isActive())
		{
			m_Display->clear();

			m_Display->swapBuffers();
		}

		// Shut-Down
		m_Display->closeDisplay();

	}

}