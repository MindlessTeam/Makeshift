// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{


	// Display
	// --------------------------------------------
	// Display handling
	class Display
	{

	public:
		Display() {};
		~Display() = default;

	public:
		void createDisplay();
		void clear();
		void swapBuffers();

		bool isActive();

	};

}