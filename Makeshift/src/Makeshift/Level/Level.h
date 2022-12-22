// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <vector>

namespace Makeshift
{

	struct Entity;

	// Level
	// --------------------------------------------
	// Class representing a game level, contains a
	// vector of entities, as well as a variety of 
	// functions to manage entities.
	class Level
	{

	public:
		Level() {}
		~Level() = default;

		void update();

	public:
		//TODO: Entity functions!

	private:
		std::vector<Entity*> m_Entities;

		int generateID();

	};

}