// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	// Time
	// ---------------------------------------------
	// Struct to keep track of time and deltaTime.
	struct Time
	{

	public:
		// Time::getDeltaTime()
		// -----------------------------------------
		// Returns the delta time (i.e. the time
		// between the current and last frame).
		static float getDeltaTime() { return s_DeltaTime; }
		
		// Time::getElapsed()
		// -----------------------------------------
		// Returns the time that has passed since
		// the engine started.
		//NOTE: Not necessarily accurate to actual seconds!
		static float getElapsed() { return s_Elapsed; }

	public:
		// Time::updateTime()
		// -----------------------------------------
		// Recalculates all the Time variables. Call
		// this every frame.
		static void updateTime();

	private:
		static float s_DeltaTime;
		static float s_LastFrame;
		static float s_Elapsed;

	};

}