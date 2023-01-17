// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Level.h"

#include "Makeshift/Utility/Random.h"
#include "Makeshift/Debug/Log.h"

namespace Makeshift
{

	int Level::generateID()
	{
		DEBUG_TRACE("Makeshift::Level::generateID()");
		
		bool available = true;
		int ID = Util::Random::generateRandomInt();

		if (ID == NULL)
		{
			available = false;
		}

		for (auto entity = m_Entities.begin(); entity != m_Entities.end(); entity++)
		{
			if (entity->first == ID)
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

	void Level::update()
	{

		for (auto entity = m_Entities.begin(); entity != m_Entities.end(); entity++)
		{
			entity->second->update();
		}

	}

	void Level::removeEntity(int ID)
	{

		for (auto entity = m_Entities.begin(); entity != m_Entities.end(); entity++)
		{
			if (entity->first == ID)
			{
				m_Entities.erase(entity);
			}
		}

		DEBUG_WARN("Attempted to remove non-existant entity {}!", ID);

	}

template<typename T>
	int Level::addEntity()
	{
		DEBUG_FATAL("Unimplemented function!");
	}

}