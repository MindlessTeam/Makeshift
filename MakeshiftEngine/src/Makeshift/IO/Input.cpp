// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Makeshift
{

	void Input::pollInput()
	{
		glfwPollEvents();
	}

}