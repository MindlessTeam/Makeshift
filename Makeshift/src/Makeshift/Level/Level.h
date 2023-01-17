// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Entity.h"

#include <map>
#include <memory>

namespace Makeshift
{

	// Level
	// --------------------------------------
	// A class representing a game-level, 
	// contains all entities in that level.
	class Level
	{

	public:
		

	private:
		std::map<int, std::shared_ptr<Entity>> m_Entities;

	};

}