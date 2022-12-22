// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <vector>

namespace Makeshift
{

	struct Entity;

	class Level
	{

	public:
		Level() {}
		~Level() = default;

		void update();

	private:
		std::vector<Entity*> m_Entities;

		int generateID();

	};

}