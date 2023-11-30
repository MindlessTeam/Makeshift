// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

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
		virtual void load(const std::string& location) = 0;
		virtual void save(const std::string& location) = 0;
		virtual void save() {};
		// The save function remains empty-bodied for most resources
		// since most resources are static (meaning: they are loaded
		// and not modified). However, this function exists for
		// resources that need to/can be modified. (e.g. a terrain)

		virtual void renderIMGUI() {};

	};

}