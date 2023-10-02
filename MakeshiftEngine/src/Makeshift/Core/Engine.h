// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Makeshift/Graphics/Display.h"
#include "Makeshift/Resource/ResourceMap.h"
#include "Makeshift/Level/Level.h"

#include <memory>

#include <imgui/imgui.h>

namespace Makeshift
{

	// Makeshift Engine
	// --------------------------------------------
	// Application base class, all Makeshift applications
	// are built on-top of this.
	class Engine
	{

	public:
		Engine() {}
		virtual ~Engine() = default;

		void run();

	public:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void cleanUp() = 0;

	public:
		std::shared_ptr<Display> getDisplay() const { return m_Display; }
		std::shared_ptr<ResourceMap> getResourceMap() const { return m_ResourceMap; }
		std::shared_ptr<Level> getActiveLevel() const { return m_ActiveLevel; }


	public:
		int getCurrentSaveGame() { return m_CurrentSaveGame; }
		void setSaveGame(int number);

		void loadLevel(const std::string& name, bool savegame);
		void quickSave();

		void quit();


	private:
		std::shared_ptr<Display> m_Display;
		std::shared_ptr<ResourceMap> m_ResourceMap;
		std::shared_ptr<Level> m_ActiveLevel;

	private:
		int m_CurrentSaveGame = 0;

		// -------------------------------------------------------

	public:
		static Engine& getInstance() { return *s_Instance; }
	private:
		static Engine* s_Instance;

	};

}