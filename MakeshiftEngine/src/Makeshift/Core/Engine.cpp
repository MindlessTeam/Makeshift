// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
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
		m_Display = std::make_unique<Display>();

		// Initialization ----------------------------
		m_Display->createDisplay();

		init();

		// Game Loop ---------------------------------
		while (m_Display->isActive())
		{
			m_Display->clear();

			Input::pollInput();
			update();

			m_Display->swapBuffers();
		}

		cleanUp();

		// Shut-Down ---------------------------------
		m_Display->closeDisplay();

	}

}