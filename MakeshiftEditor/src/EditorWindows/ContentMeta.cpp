// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ContentMeta.h"

#include <Makeshift/Debug/Log.h>

#include <json/json.h>

#include <fstream>

namespace MakeshiftEditor
{

	void ContentMeta::loadJson(Json::Value root)
	{
		DEBUG_TRACE("MakeshiftEditor::ContentMeta::loadJson()");

		const Json::Value& resources = root["Resources"];
		for (const Json::Value& resource : resources)
		{
			std::string location = resource["Location"].asString();
			std::string type = resource["Type"].asString();

			const Json::Value JSONversion = resource["Version"];
			Version version = Version(JSONversion["major"].asInt(), JSONversion["minor"].asInt(), JSONversion["patch"].asInt());

			m_Data.m_Resources.emplace(location, std::make_pair(type, version));
		}

	}

	void ContentMeta::addEntry(const std::string& location)
	{
		DEBUG_TRACE("MakeshiftEditor::ContentMeta::addEntry()");

		if (location.empty())
		{
			DEBUG_WARN("Location parameter is empty!");
			return;
		}

		std::ifstream file(location);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open JSON file '{}'", location);
			m_Data.m_Resources.emplace(location, std::make_pair("CORRUPT", Version()));
			return;
		}

		Json::CharReaderBuilder reader;
		std::string errors;

		Json::Value root;

		if (!Json::parseFromStream(reader, file, &root, &errors))
		{
			file.close();
			DEBUG_ERROR("Failed to parse JSON from file '{}' with errors '{}'", location, errors);
			m_Data.m_Resources.emplace(location, std::make_pair("CORRUPT", Version()));
			return;
		}

		file.close();

		std::string type = root["Type"].asString();
		const Json::Value JSONversion = root["Version"];
		Version version = Version(JSONversion["major"].asInt(), JSONversion["minor"].asInt(), JSONversion["patch"].asInt());

		m_Data.m_Resources.emplace(location, std::make_pair(type, version));

	}

}