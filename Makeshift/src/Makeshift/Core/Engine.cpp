// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Engine.h"

#include "Makeshift/Debug/Log.h"

namespace Makeshift
{

	Engine* Engine::s_Instance = nullptr; // "Singleton"

	void Engine::run()
	{

		if (s_Instance != nullptr)
			return;

		s_Instance = this;
		Log::init();

		// Initialize the pointers
		m_Display = new Display();

		// Initialization ----------------------------
		m_Display->createDisplay();

		// Game Loop ---------------------------------
		while (m_Display->isActive())
		{
			m_Display->clear();

			m_Display->swapBuffers();
		}

		// Shut-Down ---------------------------------
		m_Display->closeDisplay();

	}

}