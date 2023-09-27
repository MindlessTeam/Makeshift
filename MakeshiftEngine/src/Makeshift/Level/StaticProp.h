// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Level/Entity.h>

namespace Makeshift
{

	// StaticProp - Entity
	// --------------------------------------
	// <description>
	class StaticProp : public Entity
	{

	public:
		std::string getName() override
		{
			return "StaticProp";
		}

	public:
		void serialize(Json::Value& value) override {}
		void deSerialize(Json::Value value) override {}

	protected:
		// Initialize all your resources here
		void onInit() override {}
		// This function is called every frame.
		void onUpdate() override {}

		void onEnable() override {}
		void onDisable() override {}

	private: // Resources
		

	};

}