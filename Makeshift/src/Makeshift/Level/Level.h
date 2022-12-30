// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Makeshift/Resource/Resource.h"

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace Makeshift
{

	struct Entity;

	class Level
	{

	public:
		Level() {}
		~Level() = default;

		void update();

	public:

	public:


	private:
		std::map<std::string, Resource*> m_Resources;
		std::vector<Entity*> m_Entities;

	};

}