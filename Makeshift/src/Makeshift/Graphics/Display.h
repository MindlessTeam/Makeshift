// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{


	// Display
	// --------------------------------------------
	// Base Abstraction class for the Display
	class Display
	{

	public:
		Display() {};
		virtual ~Display() = default;

		static Display* create();

	public:
		virtual void createDisplay() = 0;
		virtual void clear() = 0;
		virtual void swapBuffers() = 0;

		virtual bool isActive() = 0;

	};

}