// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	struct Time
	{

	public:
		static float getDeltaTime() { return s_DeltaTime; }
		static float getElapsed() { return s_Elapsed; }

	public:
		static void updateTime();

	private:
		static float s_DeltaTime;
		static float s_LastFrame;
		static float s_Elapsed;

	};

}