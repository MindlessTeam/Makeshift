// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	// Entity
	// -----------------------------------------
	// Base class for all entities.
	class Entity
	{

	public:
		void init() { onInit(); } // onInit() is a theoretically redundant function,
								  // but for the sake of consistency the pass-through
								  // function init() exists. The compiler is gonna 
								  // optimize the hell out of my code anyway, so 
								  // why not encourage it?!
		void update() { if (m_IsEnabled) { onUpdate(); } }

		void enable() { m_IsEnabled = true; onEnable(); }
		void disable() { m_IsEnabled = false; onDisable(); }

	protected: // could be private, I guess...
		virtual void onInit() = 0;
		virtual void onUpdate() = 0;

		virtual void onEnable() = 0;
		virtual void onDisable() = 0;

	private:
		bool m_IsEnabled = false;

	};

}