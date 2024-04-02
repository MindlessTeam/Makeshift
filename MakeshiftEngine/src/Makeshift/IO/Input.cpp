// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Input.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Makeshift
{

	void Input::pollInput()
	{
		DEBUG_TRACE("Makeshift::Input::pollInput()");

		glfwPollEvents();
	}

}