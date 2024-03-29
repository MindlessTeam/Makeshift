// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Time.h"

#include <GLFW/glfw3.h>

namespace Makeshift
{

	float Time::s_DeltaTime = 0.0f;
	float Time::s_Elapsed = 0.0f;
	float Time::s_LastFrame = 0.0f;

	void Time::updateTime()
	{

		float currentFrame = glfwGetTime();
		s_DeltaTime = currentFrame - s_LastFrame;
		s_LastFrame = currentFrame;

		s_Elapsed += s_DeltaTime;

	}

}