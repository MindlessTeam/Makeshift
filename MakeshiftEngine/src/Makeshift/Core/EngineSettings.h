// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/Graphics/Display.h"

namespace Makeshift
{

	// EngineSettings - Resource
	// --------------------------------------
	// Essentially functions as a INI file for
	// the engine...
	//TODO: as well as for global settings relating to graphics, audio, etc.
	struct EngineSettings : public Resource
	{

	public:
		std::string getType() override
		{
			return "EngineSettings";
		}

	public:
		struct Data
		{
			std::string mainMenu;
			DisplaySettings displaySettings;
		};

	public:
		~EngineSettings() = default;

		Data& getData() { return m_Data; }
		void setData(Data data) { m_Data = data; }

	public:
		void loadJson(Json::Value root) override;
		
		void loadDefaultValues() override;

	public:
		static void saveEngineSettings( const std::string& location,
			std::string mainMenu,
			DisplaySettings displaySettings);

	private:
		Data m_Data;

	};

}