// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Level.h"

#include "Makeshift/Utility/FileSystem.h"

#include <json/json.h>
#include <fstream>

namespace Makeshift
{

	std::map<std::string, std::function<std::shared_ptr<Entity>()>> EntityRegistry::s_EntityRegistry;

	std::shared_ptr<Entity> EntityRegistry::createEntity(std::string name)
	{

		auto entity = s_EntityRegistry.find(name);
		if (entity != s_EntityRegistry.end())
		{
			return std::dynamic_pointer_cast<Entity>((entity->second)());
		}

	}

	void Level::addEntity(std::shared_ptr<Entity> entity)
	{
		DEBUG_TRACE("Makeshift::Level::addEntity()");

		DEBUG_INFO("Adding Entity '{}' to Level...", entity->getName());

		m_EntityMap.emplace(m_Entities, entity);
		m_Entities++;

		entity->init();
	}

	void Level::removeEntity(uint64_t ID)
	{
		DEBUG_TRACE("Makeshift::Level::removeEntity()");

		auto entity = m_EntityMap.find(ID);
		if (entity != m_EntityMap.end())
		{
			entity->second->disable();
			m_EntityMap.erase(entity);
		}



	}

	void Level::update()
	{

		for each (auto entity in m_EntityMap)
		{
			entity.second->update();
		}

	}

	void Level::load(const std::string& location)
	{

		DEBUG_TRACE("Makeshift::Level::load()");

		DEBUG_INFO("Loading Level-File '{}'", location);

		std::ifstream file(location);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open JSON file '{}'", location);
			return;
		}

		Json::CharReaderBuilder reader;
		std::string errors;

		DEBUG_INFO("Parsing Level-Data from JSON...", location);

		Json::Value root;

		if (!Json::parseFromStream(reader, file, &root, &errors))
		{
			file.close();
			DEBUG_ERROR("Failed to parse JSON from file '{}' with errors '{}'", location, errors);
			return;
		}

		file.close();

		int entityCount = root["EntityCount"].asInt();
		m_Entities = entityCount;
		m_LevelName = root["LevelName"].asString();

		const Json::Value& entities = root["Entities"];
		if (entities.isNull())
		{
			DEBUG_WARN("Loading empty level");
			return;
		}

		for (const Json::Value& entityNode : entities)
		{

			int entityID = entityNode["ID"].asInt();

			std::shared_ptr<Entity> entity = EntityRegistry::createEntity(entityNode["Type"].asString());
			entity->deSerialize(entityNode);

			m_EntityMap.emplace(entityID, entity);

		}

	}

	void Level::save(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Level::save()");

		int entityCount = m_Entities;

		DEBUG_INFO("Parsing Level-Info to JSON...");

		Json::Value root;

		root["LevelName"] = m_LevelName;
		root["EntityCount"] = entityCount;

		Json::Value entities;
		for (const auto& entity : m_EntityMap)
		{

			Json::Value entityNode;

			entityNode["Type"] = entity.second->getName();
			entityNode["ID"] = entity.first;
			entity.second->serialize(entityNode);

			entities.append(entityNode);

		}

		root["Entities"] = entities;

		DEBUG_INFO("Writing Level-File '{}'...", location + m_LevelName + ".json");

		Json::StyledWriter writer;

		std::ofstream file(location + m_LevelName + ".json");
		if (file.is_open())
		{
			file << writer.write(root);
			file.close();
		}
		else
		{
			DEBUG_ERROR("Failed to write Level-File to location '{}'", location + m_LevelName + ".json");
		}

	}

}