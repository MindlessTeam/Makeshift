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

	std::shared_ptr<Resource> ResourceMap::getResource(int ID)
	{
		
		for (auto resource = m_Resources.begin(); resource != m_Resources.end(); resource++)
		{
			if (resource->second.first == ID)
			{
				return resource->second.second;
			}
		}

		return nullptr;

	}

	std::shared_ptr<Resource> ResourceMap::getResource(const std::string& source)
	{

		auto resource = m_Resources.find(source);
		if (resource != m_Resources.end())
		{
			return resource->second.second;
		}

		return nullptr;

	}

	void ResourceMap::unloadResource(int ID)
	{

		for (auto resource = m_Resources.begin(); resource != m_Resources.end(); resource++)
		{
			if (resource->second.first == ID)
			{
				m_Resources.erase(resource->first);
			}
		}

	}

	void ResourceMap::unloadResource(const std::string& source)
	{

		auto resource = m_Resources.find(source);
		if (resource != m_Resources.end())
		{
			m_Resources.erase(resource->first);
		}

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

		m_Resources.insert(std::make_pair(source, std::make_pair(ID, std::make_shared<Resource>(Util::FileSystem::loadMesh(source)))));

		return ID;

	}

}