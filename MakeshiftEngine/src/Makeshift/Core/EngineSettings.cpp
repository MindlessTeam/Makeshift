// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "EngineSettings.h"

#include "Makeshift/Version.h"

#include "Makeshift/Debug/Log.h"

#include <json/json.h>

#include <fstream>

namespace Makeshift
{

	void EngineSettings::loadJson(Json::Value root)
	{

		m_Data.mainMenu = root["Levels"]["MainMenu"].asString();

		m_Data.displaySettings.width = root["Settings"]["Display"]["Width"].asInt();
		m_Data.displaySettings.height = root["Settings"]["Display"]["Height"].asInt();

		m_Data.displaySettings.VSync = root["Settings"]["Display"]["VSync"].asBool();

		switch (root["Settings"]["Display"]["Mode"].asInt())
		{
		default:
			m_Data.displaySettings.mode = DisplaySettings::WINDOWED;
			break;
		case 2:
			m_Data.displaySettings.mode = DisplaySettings::FULLSCREEN;
			break;
		}

	}

	void EngineSettings::loadDefaultValues()
	{

		m_Data.mainMenu = "";

		m_Data.displaySettings.width = 1280;
		m_Data.displaySettings.height = 720;

		m_Data.displaySettings.VSync = true;

		m_Data.displaySettings.mode = DisplaySettings::WINDOWED;

	}

	void EngineSettings::saveEngineSettings(const std::string& location, std::string mainMenu, DisplaySettings displaySettings)
	{
		DEBUG_TRACE("Makeshift::EngineSettings::saveEngineSettings()");

		Json::Value root;

		root["Type"] = "EngineSettings";
		root["Version"]["major"] = VERSION_MAJOR;
		root["Version"]["minor"] = VERSION_MINOR;
		root["Version"]["patch"] = VERSION_PATCH;

		Json::Value levels;

		levels["MainMenu"] = mainMenu;
		
		root["Levels"] = levels;

		Json::Value settings;

		Json::Value display;

		switch (displaySettings.mode)
		{
		case DisplaySettings::WindowMode::WINDOWED:
			display["Mode"] = 1;
			break;
		case DisplaySettings::WindowMode::FULLSCREEN:
			display["Mode"] = 2;
			break;
		}

		display["Width"] = displaySettings.width;
		display["Height"] = displaySettings.height;

		display["VSync"] = displaySettings.VSync;

		settings["Display"] = display;

		root["Settings"] = settings;

		std::ofstream file(location);
		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open file '{}' for writing!", location);
			file.close();
			return;
		}

		Json::StyledWriter writer;
		file << writer.write(root);
		file.close();

	}

}