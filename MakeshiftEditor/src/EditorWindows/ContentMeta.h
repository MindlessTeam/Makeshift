// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include <Makeshift/Version.h>

#include <memory>

#include <unordered_map>

namespace MakeshiftEditor
{

	// Content Meta - Resource
	// ---------------------------------------------
	// A file used by the FileBrowser to
	// determine the type of resources
	struct ContentMeta : public Makeshift::Resource
	{

	public:
		// Inherited via Resource
		std::string getType() override
		{
			return "ContentMeta";
		}

	public:
		struct Data
		{
			std::unordered_map<std::string, std::pair<std::string, Version>> m_Resources;
			// [location | type | version]
		};

	public:
		~ContentMeta() = default;

		Data& getData() { return m_Data; }
		void setData(Data data) { m_Data = data; }

	public:
		// ContentMeta::addEntry()
		// -----------------------------------------
		// Adds an entry to the ContentMeta.
		//
		// Parameters:
		// - location: the location of the resource to be added
		void addEntry(const std::string& location);

	public:
		// Inherited via Resource
		virtual void loadJson(Json::Value) override;

	private:
		Data m_Data;

	};

}