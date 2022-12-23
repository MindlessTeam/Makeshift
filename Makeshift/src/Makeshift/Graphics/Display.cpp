// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Display.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

namespace Makeshift
{

	void Display::createDisplay()
	{

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE); // TODO: handle window settings

		m_Window = glfwCreateWindow(1280, 720, "MAKESHIFT", nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	}

	void Display::closeDisplay()
	{

		glfwDestroyWindow(m_Window);
		glfwTerminate();

	}

	void Display::clear()
	{

		// TEMP -------------------
		glfwPollEvents();
		// ------------------------
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void Display::swapBuffers()
	{

		glfwSwapBuffers(m_Window);

	}

	bool Display::isActive()
	{

		return !glfwWindowShouldClose(m_Window);

	}

}
