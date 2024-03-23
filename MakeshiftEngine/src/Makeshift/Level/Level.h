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
	// -----------------------------------------
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
		void addEntity(std::shared_ptr<Entity> entity);

		template<typename T>
		std::shared_ptr<T> getEntity(uint64_t ID);

		void removeEntity(uint64_t ID);

	public:
		void update();

		virtual void loadJson(Json::Value root) override; 

		void loadSaveData();
		void saveSaveData();

	public:
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

	class EntityRegistry
	{

	public:
		template<typename T>
		static void registerEntity();

	public:
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