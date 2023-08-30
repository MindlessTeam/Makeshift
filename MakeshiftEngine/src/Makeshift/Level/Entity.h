// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>
#include <json/json.h>

namespace Makeshift
{

	// Entity
	// -----------------------------------------
	// Base class for game entities.
	// Entities make up the logic of a
	// level.
	class Entity
	{

	public:
		Entity() {}
		virtual ~Entity() = default;

	public:
		// onInit() is a theoretically redundant function,
		// init() exists purely for consistency. 
		// The compiler is gonna optimize the hell out of 
		// my code anyway, so why not encourage it?!
		void init() { onInit(); }
		void update() { if (m_IsEnabled) { onUpdate(); } }

		void enable() { m_IsEnabled = true; onEnable(); }
		void disable() { m_IsEnabled = false; onDisable(); }

	public:
		virtual void serialize(Json::Value &value) = 0;
		virtual void deSerialize(Json::Value value) = 0;

	public:
		virtual std::string getName() = 0;

	protected:
		virtual void onInit() = 0;
		virtual void onUpdate() = 0;

		virtual void onEnable() = 0;
		virtual void onDisable() = 0;

	private:
		bool m_IsEnabled = false;

	};

}