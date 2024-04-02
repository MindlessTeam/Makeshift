// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
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
		// Entity::init()
		// -----------------------------------------
		// Initializes the entity.
		void init() { onInit(); }
		// onInit() is a theoretically redundant function,
		// init() exists purely for consistency. 
		// The compiler is gonna optimize the hell out of 
		// my code anyway, so why not encourage it?!

		// Entity::update()
		// -----------------------------------------
		// Updates the entity (providing it is 
		// enabled).
		void update() { if (m_IsEnabled) { onUpdate(); } }

		// Entity::enable()
		// -----------------------------------------
		// Enables the entity.
		void enable() { m_IsEnabled = true; onEnable(); }

		// Entity::disable()
		// -----------------------------------------
		// Disables the entity.
		void disable() { m_IsEnabled = false; onDisable(); }

	public:
		// Entity::serialize()
		// -----------------------------------------
		// Serializes the data of the Entity to
		// JSON.
		virtual void serialize(Json::Value &value) = 0;

		// Entity::deSerialize()
		// -----------------------------------------
		// Reads the Entity Data from JSON.
		virtual void deSerialize(Json::Value value) = 0;

	public:
		// Entity::getName()
		// -----------------------------------------
		// Returns:
		// - the name of the entity (e.g. "SoundSource")
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