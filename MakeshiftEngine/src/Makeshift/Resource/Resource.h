// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace Json // Forward declaration
{
	struct Value;
}

namespace Makeshift
{
	// Resource
	// -----------------------------------------
	// Base class for all resources. 
	// A resource contains data, e.g. a texture.
	class Resource
	{

	public:
		virtual ~Resource() = default;

	public:
		std::string m_Location; // WHY?! I hate this.

	public:
		void load(const std::string& location);

		virtual void save() {};
		// The save function remains empty-bodied for most resources
		// since most resources are static (meaning: they are loaded
		// and not modified). However, this function exists for
		// resources that need to/can be modified. (e.g. a terrain)

	public:
		virtual std::string getType() = 0;

	protected:
		virtual void loadJson(Json::Value root) = 0;
		virtual void loadJsonLegacy(Json::Value root);
	
	};

}