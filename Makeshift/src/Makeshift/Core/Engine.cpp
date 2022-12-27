// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Engine.h"

#include "Makeshift/Debug/Log.h"

namespace Makeshift
{

	Engine* Engine::s_Instance = nullptr;

	void Engine::run()
	{

		if (s_Instance != nullptr)
			return;

		s_Instance = this;
		Log::init();

		// Initialize the pointers
		m_Display = new Display();

		// Begin Initialization
		m_Display->createDisplay();

		Log::log("It's beginning!");
		Log::log(LEVEL_WARN, "I'm serious, it's starting now!");
		Log::log(LEVEL_ERROR, "Makeshift::Engine::run()", "You're not believing me, are you? Well HERE IT COMES!");

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