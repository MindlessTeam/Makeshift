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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Makeshift/Level/Entities/StaticProp.h"
#include "Makeshift/ShaderTest.h"

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

		ImGuiRenderer::initializeImGui();

		// Registering Engine Entities
		EntityRegistry::registerEntity<StaticProp>();
		EntityRegistry::registerEntity<ShaderTest>();
		// -------------------------------------------

		m_ActiveLevel = std::make_shared<Level>();
		//m_LoadingScreen = std::make_shared<Level>();

		//m_ActiveLevel = m_ResourceMap->addResource<Level>(FileLocations::levelLocation(false) + "mainMenu" + ".json");
		//m_LoadingScreen = m_ResourceMap->addResource<Level>(FileLocations::levelLocation(false) + "loadingScreen" + ".json");

		init();

		// Game Loop ---------------------------------
		while (m_Display->isActive())
		{
			m_Display->clear();

			Time::updateTime();
			ImGuiRenderer::prepareFrame();

			Input::pollInput();
			update();

			ImGuiRenderer::endFrame();

			m_ActiveLevel->update();
			m_Display->swapBuffers();
		}

		cleanUp();

		ImGuiRenderer::cleanUp();

		// Shut-Down ---------------------------------
		m_Display->closeDisplay();

	}

	void Engine::setSaveGame(int number)
	{

		m_CurrentSaveGame = number;
		FileSystem::initSaveGame();

	}

	void Engine::loadLevel(const std::string& name, bool savegame)
	{
		DEBUG_TRACE("Makeshift::Engine::loadLevel()");

		// ShowLoadingScreen
		if (m_CurrentSaveGame != 0)
		{
			m_ActiveLevel->saveSaveData();
		}

		m_ResourceMap->removeResource(m_ActiveLevel->m_Location);
		m_ActiveLevel = m_ResourceMap->addResource<Level>(FileLocations::levelLocation(false) + name + ".json");

		if (savegame)
		{
			m_ActiveLevel->loadSaveData();
		}

	}

	void Engine::quickSave()
	{
		DEBUG_TRACE("Makeshift::Engine::quickSave()");

		int tmp = m_CurrentSaveGame;
		setSaveGame(0);
		m_ActiveLevel->saveSaveData();
		setSaveGame(tmp);

	}

	void Engine::quit()
	{

		quickSave();
		
		glfwSetWindowShouldClose(getDisplay()->getNativeWindow(), true);

	}

}