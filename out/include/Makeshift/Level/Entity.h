// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	// Base Entity
	// --------------------------------------------
	// Base entity class, contains all virtual functions,
	// the entities ID, and an option for enabling and
	// disabling.
	struct Entity
	{

	public:
		Entity() {}
		Entity(int ID) { m_ID = ID; }
		~Entity() = default;

		void setID(int ID) { m_ID = ID; }
		int* getID() { return &m_ID; }

		void enable() { m_IsEnabled = true; onEnable(); }
		void disable() { m_IsEnabled = false; onDisable(); }

	public:
		virtual void init() = 0;
		virtual void close() = 0;

		virtual void execute() = 0;

	private: // These functions are private because they are not
		// meant to be accessed externally, that is the job of the
		// enable() and disable() functions. 
		virtual void onEnable() = 0;
		virtual void onDisable() = 0;

	private:
		int m_ID;
		bool m_IsEnabled = false;

	};

}