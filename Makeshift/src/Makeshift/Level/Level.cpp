// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Level.h"

#include "Entity.h"

#include "Makeshift/Utility/Random.h"

namespace Makeshift
{

	void Level::update()
	{

		for each (Entity* entity in m_Entities)
		{
			entity->execute();
		}

	}
	
	int Level::generateID()
	{

		int ID = Util::Random::generateRandomInt();
		bool isAvailable = true;

		for each (Entity* entity in m_Entities)
		{
			if (&ID == entity->getID()) 
			{
				isAvailable = false;
			}
		}

		if (!isAvailable)
		{
			return generateID();
		}

		return ID;

	}

}