// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Level.h"

#include "Makeshift/Utility/FileSystem.h"

#include "Makeshift/Utility/Random.h"

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

		m_EntityMap.emplace(generateID(), std::make_pair(false, entity));

		entity->init();
	}

	void Level::removeEntity(uint64_t ID)
	{
		DEBUG_TRACE("Makeshift::Level::removeEntity()");

		auto entity = m_EntityMap.find(ID);
		if (entity != m_EntityMap.end())
		{
			entity->second.second->disable();
			m_EntityMap.erase(entity);
		}

	}

	void Level::update()
	{

		for each (auto entity in m_EntityMap)
		{
			entity.second.second->update();
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
			bool saveState = entityNode["SaveState"].asBool();

			std::shared_ptr<Entity> entity = EntityRegistry::createEntity(entityNode["Type"].asString());
			entity->deSerialize(entityNode);

			m_EntityMap.emplace(entityID, std::make_pair(saveState, entity));
			entity->enable();

		}

	}

	void Level::save(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Level::saveComplete()");

		std::string writeLocation = FileLocations::levelLocation(false) + m_LevelName + ".json";

		DEBUG_INFO("Parsing Level-Info to JSON...");

		Json::Value root;

		root["LevelName"] = m_LevelName;

		Json::Value entities;
		for (const auto& entity : m_EntityMap)
		{

			Json::Value entityNode;

			entityNode["Type"] = entity.second.second->getName();
			entityNode["ID"] = entity.first;
			entityNode["SaveState"] = entity.second.first;
			entity.second.second->serialize(entityNode);

			entities.append(entityNode);

		}

		root["Entities"] = entities;

		DEBUG_INFO("Writing Level-File '{}'...", writeLocation);

		Json::StyledWriter writer;

		std::ofstream file(writeLocation);
		if (file.is_open())
		{
			file << writer.write(root);
			file.close();
		}
		else
		{
			DEBUG_ERROR("Failed to write Level-File to location '{}'", writeLocation);
		}

	}

	void Level::loadSaveData()
	{
		DEBUG_TRACE("Makeshift::Level::loadSaveData()");

		std::string loadLocation = FileLocations::levelLocation(true) + m_LevelName + ".json";

		DEBUG_INFO("Loading Level-Save-Data '{}'", loadLocation);

		std::ifstream file(loadLocation);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open JSON file '{}'", loadLocation);
			return;
		}

		Json::CharReaderBuilder reader;
		std::string errors;

		DEBUG_INFO("Parsing Level-Data from JSON...", loadLocation);

		Json::Value root;

		if (!Json::parseFromStream(reader, file, &root, &errors))
		{
			file.close();
			DEBUG_ERROR("Failed to parse JSON from file '{}' with errors '{}'", loadLocation, errors);
			return;
		}

		file.close();
	}

	void Level::saveSaveData()
	{
		DEBUG_TRACE("Makeshift::Level::saveSaveData()");

		std::string writeLocation = FileLocations::levelLocation(true) + m_LevelName + ".json";

		DEBUG_INFO("Parsing Level-Save-Data to JSON...");
	
		Json::Value root;

		root["AssociatedLevel"] = m_LevelName;

		Json::Value entities;
		for (const auto& entity : m_EntityMap)
		{

			if (entity.second.first)
			{
				Json::Value entityNode;

				entityNode["Type"] = entity.second.second->getName();
				entityNode["ID"] = entity.first;
				entity.second.second->serialize(entityNode);

				entities.append(entityNode);
			}

		}

		root["Entities"] = entities;

		DEBUG_INFO("Writing Level-Save-Data '{}'...", writeLocation);

		Json::StyledWriter writer;

		std::ofstream file(writeLocation);
		if (file.is_open())
		{
			file << writer.write(root);
			file.close();
		}
		else
		{
			DEBUG_ERROR("Failed to write Level-Save-Data to location '{}'", writeLocation);
		}

	}

	int Level::generateID()
	{
		DEBUG_TRACE("Makeshift::Level::generateID()");

		int ID = Util::Random::generateRandomInt();

		for (auto entity : m_EntityMap)
		{
			if (entity.first == ID)
			{
				DEBUG_WARN("Attempted to generate already existing ID! - '{}'", ID);
				return generateID();
			}
		}

		return ID;

	}

}