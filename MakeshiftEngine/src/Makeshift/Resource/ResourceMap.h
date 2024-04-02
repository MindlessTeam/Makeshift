// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
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
    // ---------------------------------------------
    // A class representing all loaded
    // resources.
    class ResourceMap
    {

    public:
        ResourceMap();
        ~ResourceMap() = default;

    public:
        // ResourceMap::addResource()
        // -----------------------------------------
        // Adds a resource to the resource map.
        //
        // Parameters:
        // - <T>: the type of resource to be cast to after loading/generation
        // - source: the source location of the resource
        // - codeGeneration: when true expects the engine to generate the resources Data elsewhere, therefore creates an empty resource with the assigned location slot
        //
        // Returns:
        // - a shared_ptr to the loaded/generated resource
        template<typename T>
        std::shared_ptr<T> addResource(const std::string& source, bool codeGeneration = false);

        // ResourceMap::getResource()
        // -----------------------------------------
        // Gets a resource from the resource map.
        //
        // Parameters:
        // - <T>: the type of resource to be cast to
        // - source: the source location of the resource
        // 
        // Returns:
        // - a shared_ptr to the found resource (or nullptr if it couldn't be found)
        template<typename T>
        std::shared_ptr<T> getResource(const std::string& source);

        // ResourceMap::removeResource()
        // -----------------------------------------
        // Removes a resource from the resource map.
        //NOTE: If the resource is still in use elsewhere, it will remain.
        // 
        // Parameters:
        // - source: the source location of the resource
        void removeResource(const std::string& source);

    public:
        // ResourceMap::getResources()
        // -----------------------------------------
        // Returns:
        // - a pointer to the resource maps map
        std::unordered_map<std::string, std::pair<int, std::shared_ptr<Resource>>>& getResources() { return m_Resources; }


    private:
        std::unordered_map<std::string, std::pair<int, std::shared_ptr<Resource>>> m_Resources;
        // [Resource filepath | Usage count | Resource Data]

    };

    template<typename T>
    inline std::shared_ptr<T> ResourceMap::addResource(const std::string& source, bool codeGeneration)
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

        if(!codeGeneration)
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