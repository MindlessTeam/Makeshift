// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ResourceMap.h"

#include "Mesh.h"

#include "Makeshift/Debug/Log.h"
#include "Makeshift/Utility/Random.h"
#include "Makeshift/Utility/FileSystem.h"

// I must admit that I'm rather proud of this system,
// but it is probably horribly inefficient and causes
// twenty different memory leaks in ways that I 
// won't even understand, so... COOL!

namespace Makeshift
{

	int ResourceMap::generateID()
	{
		DEBUG_TRACE("Makeshift::ResourceMap::generateID()");

		bool available = true;
		int ID = Util::Random::generateRandomInt();

		if (ID == NULL)
		{
			available = false;
		}

		for (auto resource = m_Resources.begin(); resource != m_Resources.end(); resource++)
		{
			if (resource->second.first == ID)
			{
				available = false;
			}
		}

		if (!available)
		{
			return generateID();
		}

		return ID;

	}

	int ResourceMap::getID(const std::string& source)
	{

		auto resource = m_Resources.find(source);
		if (resource != m_Resources.end())
		{
			return resource->second.first;
		}

		return NULL;

	}

	void ResourceMap::unloadResource(int ID)
	{

		for (auto resource = m_Resources.begin(); resource != m_Resources.end(); resource++)
		{
			if (resource->second.first == ID)
			{
				m_Resources.erase(resource);
			}
		}

		DEBUG_WARN("Attempted to unload non-existant resource {}!", ID);

	}

	void ResourceMap::unloadResource(const std::string& source)
	{

		auto resource = m_Resources.find(source);
		if (resource != m_Resources.end())
		{
			m_Resources.erase(resource);
		}

		DEBUG_WARN("Attempted to unload non-existant resource '{}'!", source);

	}

template<typename T>
	int ResourceMap::loadResource(const std::string& source)
	{
		DEBUG_FATAL("Unimplemented function!");
	}

	template<>
	int ResourceMap::loadResource<Mesh>(const std::string& source)
	{
		DEBUG_TRACE("Makeshift::ResourceMap::loadResource()");
	
		auto resource = m_Resources.find(source);
		if (resource != m_Resources.end())
		{
			DEBUG_WARN("Resource '{}' is already loaded!", source);
			return resource->second.first;
		}
	
		DEBUG_INFO("Loading Resource '{}'...", source);
		int ID = generateID();
	
		m_Resources.emplace(source, std::make_pair(ID, new Mesh{ Util::FileSystem::loadMesh(source) }));
	
		return ID;
	
	}

}