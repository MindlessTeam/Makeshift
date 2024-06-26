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
		// Resource::load()
		// -----------------------------------------------
		// Loads a resource.
		// 
		// Parameters:
		// - location: the location of the resource relative to the working directory
		void load(const std::string& location);

		virtual void save() {};
		// The save function remains empty-bodied for most resources
		// since most resources are static (meaning: they are loaded
		// and not modified). However, this function exists for
		// resources that need to/can be modified. (e.g. a terrain)

	public:
		// Resource::getType()
		// -----------------------------------------------
		// Returns:
		// - the type of resource as a string
		virtual std::string getType() = 0;

	protected:
		// Resource::loadJson()
		// -----------------------------------------------
		// Deserializes the resource data from .json.
		//
		// Parameters:
		// - root: the json root node to read from
		virtual void loadJson(Json::Value root) = 0;

		// Resource::loadJsonLegacy()
		// -----------------------------------------------
		// Called when the resource version is smaller
		// then the current version.
		// Meant to provide backwards-compatibility.
		//
		// Parameters:
		// - root: the json root node to read from
		virtual void loadJsonLegacy(Json::Value root);

	protected:
		// Resource::loadDefaultValues()
		// -----------------------------------------------
		// Loads the default Values for a resource.
		//
		//NOTE: This will still create a new resource in memory, which means it isn't particularly efficient. However, this function is essentially just a fallback that should in theory never be triggered so it should be fine.
		virtual void loadDefaultValues();
	
	};

}