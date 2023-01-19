// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Entity.h"

#include <memory>
#include <map>

namespace Makeshift
{

	// Level
	// --------------------------------------
	// A class representing a game-level, 
	// contains all entities in that level.
	class Level
	{

	public:
		void update();

	public:
		template<typename T>
		int addEntity();

		template<typename T>
		std::shared_ptr<T> getEntity(int ID)
		{
			for (auto entity = m_Entities.begin(); entity != m_Entities.end(); entity++)
			{
				if (entity->first == ID)
				{
					return std::dynamic_pointer_cast<T>(entity->second);
				}
			}
			return nullptr;
		}

		void removeEntity(int ID);

	private:
		std::map<int, std::shared_ptr<Entity>> m_Entities;

		int generateID();

	};

}