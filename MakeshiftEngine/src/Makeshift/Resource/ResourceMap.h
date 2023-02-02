// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Resource.h"

#include <map>
#include <memory>
#include <string>

//MAYHAPS:
// change "source" to "path"

// THE RESOURCE SYSTEM -------------------------------------------------------
// 
// Makeshifts resource system allows for (relatively) efficient 
// storage of Resources.
// 
// Instead of the required data being loaded into an entity
// directly, which would quickly result in unnescessary duplicates
// (Two Model entities rendering the same mesh would mean that
// that mesh would be loaded into memory twice), an entity
// only contains the ID of the resource on the resource map.
// 
// Since it is necessary to have a static, unchanging value to
// keep track of which entities are loaded and neither the ID
// nor the Resource itself are that the resource map also
// keeps track of the source location which, in a production
// setting, is rarely going to change.
// 
// (In theory, you could check wether the data of two resources
// is identical to determine whether it was already loaded)
// 
//TODO: [EDITOR] add option to batch-convert entity-resource-IDs to a new ID. (e.g. after a model was moved to a new location)
//TODO: Add support for resources that are not dependend on a path (e.g. default or pre-coded resources) 
//

namespace Makeshift
{

	// Resource Map
	// -----------------------------------------
	// Class to manage "allocating" and "de-
	// allocating" of resources.
	// NOTE: Use ID functions wherever possible!
	// The string functions exist as a utility,
	// but it is recommended to use them 
	// sparingly.
	class ResourceMap
	{

	public:
		ResourceMap() = default;
		~ResourceMap() = default;

	public:
		template<typename T>
		int loadResource(const std::string& source);

		int getID(const std::string& source);

		template<typename T>
		std::shared_ptr<T> getResource(int ID)
		{
			for (auto resource = m_Resources.begin(); resource != m_Resources.end(); resource++)
			{
				if (resource->second.first == ID)
				{
					return std::dynamic_pointer_cast<T>(resource->second.second);
				}
			}
			return nullptr;
		}
		template<typename T>
		T* getResource(const std::string& source)
		{
			auto resource = m_Resources.find(source);
			if (resource != m_Resources.end())
			{
				return std::dynamic_pointer_cast<T>(resource->second.second);
			}
			return nullptr;
		}
		void unloadResource(int ID);
		void unloadResource(const std::string& source);

	private:
		std::map<std::string, std::pair<int, std::shared_ptr<Resource>>> m_Resources;

		int generateID();

	};

}