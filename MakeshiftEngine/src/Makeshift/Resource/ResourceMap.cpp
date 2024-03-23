// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ResourceMap.h"

#include "Makeshift/Debug/Log.h"
#include "Makeshift/Utility/Random.h"

namespace Makeshift
{

    ResourceMap::ResourceMap()
    {

    }

    void ResourceMap::removeResource(const std::string& source)
    {
        DEBUG_TRACE("Makeshift::ResourceMap::removeResource()");

        auto resource = m_Resources.find(source);
        if (resource != m_Resources.end())
        {
            resource->second.first -= 1;
            if (resource->second.first != 0)
            {
                DEBUG_INFO("Stopped unloading, Resource is still in use.");
                return;
            }

            DEBUG_INFO("Removing Resource '{}'", source);
            

            m_Resources.erase(resource);
            return;
        }

        DEBUG_WARN("Attempted to unload non-existant resource '{}'!", source);

    }

}