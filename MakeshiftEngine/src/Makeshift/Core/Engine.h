// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Makeshift/Graphics/Display.h"
#include "Makeshift/Resource/ResourceMap.h"
#include "Makeshift/Level/Level.h"

#include "Time.h"

#include <memory>

#include <imgui/imgui.h>

namespace Makeshift
{

	// Makeshift Engine
	// ---------------------------------------------
	// Application base class, all Makeshift applications
	// are built on-top of this.
	class Engine
	{

	public:
		Engine() {}
		virtual ~Engine() = default;

		// Engine::run()
		// -----------------------------------------
		// Initialises the engine and starts the
		// game-loop.
		void run();

	public:
		// Engine::init()
		// -----------------------------------------
		// Called after main initialization steps 
		// are finished. Use it to initialize whatever
		// resources and/or data your application 
		// needs.
		virtual void init() = 0;

		// Engine::update()
		// -----------------------------------------
		// Called every frame. All your gameplay
		// (or similar) logic goes here. IMGUI
		// and UI-Code goes here as well.
		virtual void update() = 0;

		// Engine::cleanUp()
		// -----------------------------------------
		// Called right before the window is closed.
		// Clean Up any floating data here.
		virtual void cleanUp() = 0;

	public:
		// Engine::getDisplay()
		// -----------------------------------------
		// Returns a shared_ptr to the currently
		// used Display.
		std::shared_ptr<Display> getDisplay() const { return m_Display; }

		// Engine::getResourceMap()
		// -----------------------------------------
		// Returns a shared_ptr to the currently
		// used Resource Map.
		std::shared_ptr<ResourceMap> getResourceMap() const { return m_ResourceMap; }

		// Engine::getActiveLevel()
		// -----------------------------------------
		// Returns a shared_ptr to the currently 
		// active level.
		std::shared_ptr<Level> getActiveLevel() const { return m_ActiveLevel; }


	public:
		// Engine::getCurrentSaveGame()
		// -----------------------------------------
		// Returns the current Save-Game-Index. If 0
		// there's currently no save game selected.
		int getCurrentSaveGame() { return m_CurrentSaveGame; }

		// Engine::setSaveGame()
		// -----------------------------------------
		// Sets the current Save-Game-Index.
		// 
		// Parameters:
		// - number: the Index to set
		void setSaveGame(int number);

		// Engine::loadLevel()
		// -----------------------------------------
		// Unloads the current level and loads a new 
		// one. If savegame = true the new level will
		// be loaded with savegame information based
		// on the current SaveGame.
		//
		// Parameters:
		// - name: The name of the level (without.json!)
		// - savegame: Whether to load the new level with savegame data or not
		void loadLevel(const std::string& name, bool savegame);

		// Engine::quickSave()
		// -----------------------------------------
		// Saves the current SaveData to the 
		// QuickSaveLocation (WHERE???).
		void quickSave();

		// Engine::quit()
		// -----------------------------------------
		// Creates a (security-)quicksave and shuts 
		// down the engine.
		void quit();


	private:
		std::shared_ptr<Display> m_Display;
		std::shared_ptr<ResourceMap> m_ResourceMap;
		std::shared_ptr<Level> m_ActiveLevel;

	private:
		int m_CurrentSaveGame = 0; // 0 means inactive / quicksave

		// -------------------------------------------------------

	public:
		// Engine::getInstance()
		// -----------------------------------------
		// Returns a pointer to the currently active
		// Instance of Makeshift. There should only 
		// ever be one.
		static Engine& getInstance() { return *s_Instance; }
	private:
		static Engine* s_Instance;

	};

}