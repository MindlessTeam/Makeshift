// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	// Resource
	// --------------------------------------------
	// A container for data.
	class Resource
	{

	protected:
		struct Data{};

	public:
		virtual Data& getData() = 0;

	};

}