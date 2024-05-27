// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Resource.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Version.h"

#include <fstream>
#include <json/json.h>

namespace Makeshift
{

	void Resource::load(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Resource::load()");

		DEBUG_INFO("Loading {} '{}'", getType(), location);

		std::ifstream file(location);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open JSON file '{}'", location);
			return;
		}

		Json::CharReaderBuilder reader;
		std::string errors;

		Json::Value root;

		if (!Json::parseFromStream(reader, file, &root, &errors))
		{
			file.close();
			DEBUG_ERROR("Failed to parse JSON from file '{}' with errors '{}'", location, errors);
			return;
		}

		file.close();

		if (root["Type"].asString() != getType())
		{
			DEBUG_WARN("Attempting to load type '{}' using '{}'-loader!", root["Type"].asString(), getType());
			return;
		}

		const Json::Value JSONversion = root["Version"];
		Version version = Version(JSONversion["major"].asInt(), JSONversion["minor"].asInt(), JSONversion["patch"].asInt());

		if (version != Version())
		{
			DEBUG_WARN("Version mismatch in '{}': file:'{}.{}.{}' current:'{}.{}.{}'! Using Legacy Loader...",
				location,
				JSONversion["major"].asInt(),
				JSONversion["minor"].asInt(),
				JSONversion["patch"].asInt(),
				VERSION_MAJOR,
				VERSION_MINOR,
				VERSION_PATCH);

			if (version <= Version())
			{
				loadJsonLegacy(root);
				return;
			}
			else
			{
				DEBUG_ERROR("File Version is higher than Engine Version. Aborting Resource loading!");
				return;
			}

		}

		loadJson(root);

	}

	void Resource::loadJsonLegacy(Json::Value root)
	{
		DEBUG_WARN("No Legacy-Loader for '{}'!", getType());
	}

	void Resource::loadDefaultValues()
	{
		DEBUG_WARN("No Default Value for '{}'", getType());
	}

}
