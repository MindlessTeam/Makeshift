// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Resource.h"

#include "Makeshift/Debug/Log.h"

#include <memory>
#include <map>
#include <string>

namespace Makeshift
{

    // Resource Map
    // -----------------------------------------
    // A class representing all loaded
    // resources.
    class ResourceMap
    {

    public:
        ResourceMap();
        ~ResourceMap() = default;

    public:
        template<typename T>
        std::shared_ptr<T> addResource(const std::string& source);

        template<typename T>
        std::shared_ptr<T> getResource(const std::string& source);

        void removeResource(const std::string& source);

    public:
        std::unordered_map<std::string, std::pair<int, std::shared_ptr<Resource>>>& getResources() { return m_Resources; }


    private:
        std::unordered_map<std::string, std::pair<int, std::shared_ptr<Resource>>> m_Resources;
        // [Resource filepath | Usage count | Resource Data]

    };

    template<typename T>
    inline std::shared_ptr<T> ResourceMap::addResource(const std::string& source)
    {
        DEBUG_TRACE("Makeshift::ResourceMap::addResource()");

        // Checking if resource is already loaded
        auto resource = m_Resources.find(source);
        if (resource != m_Resources.end())
        {
            DEBUG_WARN("Resource '{}' is already loaded!", source);
            // Adding an instance to the usage count
            resource->second.first += 1;
            return std::dynamic_pointer_cast<T>(resource->second.second);
        }

        DEBUG_INFO("Loading Resource '{}'...", source);
        std::shared_ptr<Resource> res = std::make_shared<T>();

        res->m_Location = source;
        res->load(source);

        m_Resources.emplace(source, std::make_pair(1, res));

        return std::dynamic_pointer_cast<T>(res);

    }

    template<typename T>
    inline std::shared_ptr<T> ResourceMap::getResource(const std::string& source)
    {
        DEBUG_TRACE("Makeshift::ResourceMap::getResource()");

        // Checking if resource exists
        auto resource = m_Resources.find(source);
        if (resource != m_Resources.end())
        {
            // We do not increment the usage count when simply getting a resource
            return std::dynamic_pointer_cast<T>(resource->second.second);
        }

        DEBUG_WARN("Resource '{}' doesn't exist!");
        return nullptr;

    }

}