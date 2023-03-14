// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Resource.h"

#include <memory>
#include <map>

namespace Makeshift
{

    // Resource Map
    // -----------------------------------------
    // A class representing all loaded
    // resources
    class ResourceMap
    {

        

    private:
        std::map<std::string, std::pair<int, std::shared_ptr<Resource>>> m_Resources;
        // [Resource filepath | ID | Resource Data]

        int generateID();

    }

}