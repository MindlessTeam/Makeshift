// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Entity.h"

#include "Makeshift/Resource/Resource.h"
#include "Makeshift/Debug/Log.h"

#include <map>
#include <memory>
#include <functional>
#include <cstdint>

namespace Makeshift
{

	// Level
	// ---------------------------------------------
	// A game level. Contains all entities of
	// a level.
	class Level : public Resource
	{

	public:
		std::string getType() override
		{
			return "Level";
		}

	public:
		// Level::addEntity()
		// -----------------------------------------
		// Adds an entity to the level.
		// 
		// Parameters:
		// - entity: the entity to add
		void addEntity(std::shared_ptr<Entity> entity);

		// Level::getEntity()
		// -----------------------------------------
		// Gets an Entity based on an ID.
		// 
		// Parameters:
		// - <T>: The type of entity to cast to
		// - ID: The ID of the Entity to get
		//
		// Returns:
		// - a shared_ptr to the entity (nullptr if it couldn't be found)
		template<typename T>
		std::shared_ptr<T> getEntity(uint64_t ID);

		// Level::removeEntity()
		// -----------------------------------------
		// Removes an entity from the level.
		// 
		// Parameters:
		// - ID: The ID of the entity to remove
		void removeEntity(uint64_t ID);

	public:
		// Level::update()
		// -----------------------------------------
		// Updates all the entities in the level.
		void update();

		virtual void loadJson(Json::Value root) override; 

		// Level::loadSaveData()
		// -----------------------------------------
		// Loads the entities saved data from the 
		// current SaveGame.
		void loadSaveData();

		// Level::saveSaveData()
		// -----------------------------------------
		// Saves the (save-enabled-)entities to the
		// current SaveGame.
		void saveSaveData();

	public:
		// Level::getLevelName()
		// -----------------------------------------
		// Returns:
		// - a pointer to the levels name
		std::string& getLevelName() { return m_LevelName; }
		
	private:
		int generateID();

	private:
		std::string m_LevelName = "unknown";

	private:
		std::unordered_map<uint64_t, std::pair<bool, std::shared_ptr<Entity>>> m_EntityMap;
		// [ ID | Save-State | Entity ]

	};

	template<typename T>
	inline std::shared_ptr<T> Level::getEntity(uint64_t ID)
	{
		DEBUG_TRACE("Makeshift::Level::getEntity()");

		auto entity = m_EntityMap.find(ID);
		if (entity != m_EntityMap.end)
		{
			return std::dynamic_pointer_cast<T>(entity->second.second());
		}

		T t;

		DEBUG_WARN("Couldn't get Entity '{}' with ID: '{}'", t.getName(), ID);
		return nullptr;
		
	}

	// Entity Registry
	// ---------------------------------------------
	// A list of "registered" entities. Used in the
	// loading process to determine which entity to
	// create.
	class EntityRegistry
	{

	public:
		// EntityRegistry::registerEntity()
		// -----------------------------------------
		// Registers an Entity in the EntityRegistry.
		//
		// Parameters:
		// - <T>: The type of entity to register.
		template<typename T>
		static void registerEntity();

	public:
		// EntityRegistry::createEntity()
		// -----------------------------------------
		// Creates an Entity based on its type.
		// 
		// Parameters:
		// - name: The type of entity to create
		//
		// Returns:
		// - a shared_ptr to the created Entity
		static std::shared_ptr<Entity> createEntity(std::string name);

	private:
		static std::map<std::string, std::function<std::shared_ptr<Entity>()>> s_EntityRegistry;

	};

	template<typename T>
	inline void EntityRegistry::registerEntity()
	{
		DEBUG_TRACE("Makeshift::EntityRegistry::registerEntity()");

		T entity;

		DEBUG_INFO("Registering Entity '{}'", entity.getName());

		s_EntityRegistry[entity.getName()] = []() { return std::make_shared<T>(); };

	}

}