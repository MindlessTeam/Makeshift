// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

// Should this be in Makeshift/Core?

namespace Makeshift
{

	// Input
	// ---------------------------------------------
	// Class for handling game input.
	class Input
	{

	public:
		// Input::pollInput()
		// -----------------------------------------
		// Polls the current Input from the window.
		static void pollInput();

		//TODO: Input Handling

		// I first have to think of a structure for this system,
		// I'd quite like to support Mouse, Keyboard, and
		// Controllers with one understandable(!) system.

	};

}