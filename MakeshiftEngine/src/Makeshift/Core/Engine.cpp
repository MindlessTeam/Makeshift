// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Engine.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Utility/FileSystem.h"

#include "Makeshift/Level/Level.h"
#include "Makeshift/Level/Test.h"

#include "Makeshift/IO/Input.h"

#include "Makeshift/Graphics/ImGuiRenderer.h"

#include "Makeshift/Resource/Mesh.h"

#include <glad/glad.h>
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

		ImGuiRenderer::initializeImGui();

		// Registering Engine Entities
		EntityRegistry::registerEntity<Test>();

		m_ActiveLevel = std::make_shared<Level>();

		init();

		m_ResourceMap->addResource<Mesh>("content/mdl/test.json");

		// Game Loop ---------------------------------
		while (m_Display->isActive())
		{
			m_Display->clear();

			ImGuiRenderer::prepareFrame();

			Input::pollInput();
			update();
			m_ActiveLevel->update();

			ImGuiRenderer::endFrame();

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

	void Engine::loadLevel(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Engine::loadLevel()");

		// ShowLoadingScreen
		if (m_CurrentSaveGame != 0)
		{
			m_ActiveLevel->save(FileLocations::levelLocation(true));
		}

		m_ResourceMap->removeResource(m_ActiveLevel->m_Location);
		m_ActiveLevel = m_ResourceMap->addResource<Level>(location);

	}

	void Engine::quickSave()
	{
		DEBUG_TRACE("Makeshift::Engine::quickSave()");

		m_ActiveLevel->save(FileLocations::quickSaveLocation());

	}

	void Engine::quit()
	{

		quickSave();
		
		glfwSetWindowShouldClose(getDisplay()->getNativeWindow(), true);

	}

}