// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace Makeshift
{
	// Resource
	// -----------------------------------------
	// Base class for all resources.
	// Contains Data, as well as a way to load
	// said data. 
	class Resource
	{

	protected:
		struct Data;

	public:
		virtual bool loadData(const std::string& source) = 0;

		virtual Data* getData() = 0;

	};

}