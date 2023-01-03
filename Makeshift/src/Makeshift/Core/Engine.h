// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Makeshift/Graphics/Display.h"

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
		static Engine& getInstance() { return *s_Instance; }

	private:
		Display* m_Display;

	private:
		static Engine* s_Instance;

	};

}