// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Engine.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Utility/FileSystem.h"

#include "Makeshift/Level/Level.h"

#include "Makeshift/IO/Input.h"

#include "Makeshift/Graphics/ImGuiRenderer.h"

#include "Makeshift/Level/Entities/StaticProp.h"
#include "Makeshift/ShaderTest.h"

#include <GLFW/glfw3.h>

namespace Makeshift
{

	Engine* Engine::s_Instance = nullptr; // "Singleton"

	void Engine::run()
	{

		if (s_Instance != nullptr)
			return;

		s_Instance = this;
		Log::init();
		FileSystem::initFileSystem();

		// Initialize the pointers
		m_Display = std::make_shared<Display>();
		m_ResourceMap = std::make_shared<ResourceMap>();

		// Initialization ----------------------------
		m_Display->createDisplay();

		float DPI;
		glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &DPI, nullptr);
		ImGuiRenderer::setUISize(DPI);

		// Registering Engine Entities
		EntityRegistry::registerEntity<StaticProp>();
		EntityRegistry::registerEntity<ShaderTest>();
		// -------------------------------------------

		//m_LoadingScreen = m_ResourceMap->addResource<Level>(FileLocations::levelLocation(false) + "loadingScreen.json");

		// Initialize the applications resources
		init();

		// Game Loop ---------------------------------
		while (m_Display->isActive())
		{
			m_Display->clear();

			Time::updateTime();

			if(m_ActiveLevel != nullptr)
				m_ActiveLevel->update();

			ImGuiRenderer::prepareFrame();

			Input::pollInput();
			update();

			ImGuiRenderer::endFrame();

			m_Display->swapBuffers();
		}
		// -------------------------------------------

		cleanUp();

		ImGuiRenderer::cleanUp();

		DEBUG_INFO("Engine was active for '{}s'", Time::getElapsed());

		// Shut-Down ---------------------------------
		m_Display->closeDisplay();


	}

	void Engine::setSaveGame(int number)
	{
		DEBUG_TRACE("Makeshift::Engine::setSaveGame()");

		m_CurrentSaveGame = number;
		FileSystem::initSaveGame();

	}

	void Engine::loadLevel(const std::string& name, bool savegame)
	{
		DEBUG_TRACE("Makeshift::Engine::loadLevel()");

		//TODO: Show Loading Screen
		if (m_CurrentSaveGame != 0)
		{
			m_ActiveLevel->saveSaveData();
		}

		// Remove the old level and load the new one
		m_ResourceMap->removeResource(m_ActiveLevel->m_Location);
		m_ActiveLevel = m_ResourceMap->addResource<Level>(FileLocations::levelLocation(false) + name + ".json");

		// If there's an active SaveGame load the data into the level.
		if (savegame && m_CurrentSaveGame != 0)
		{
			m_ActiveLevel->loadSaveData();
		}

	}

	void Engine::quickSave()
	{
		DEBUG_TRACE("Makeshift::Engine::quickSave()");

		// Perhaps quick saves should be in a different folder.
		// For now we just use savegame 0 as the quicksave folder,
		// since it is an "invalid" saveGame.

		int tmp = m_CurrentSaveGame;
		setSaveGame(0);
		m_ActiveLevel->saveSaveData();
		setSaveGame(tmp);

	}

	void Engine::quit()
	{
		DEBUG_TRACE("Makeshift::Engine::quit()");

		quickSave();
		
		glfwSetWindowShouldClose(getDisplay()->getNativeWindow(), true);

	}

}