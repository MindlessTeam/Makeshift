// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Display.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

namespace Makeshift
{


	Display::~Display()
	{
		DEBUG_TRACE("Makeshift::Display::~Display()");

		glfwTerminate();
	}

	void Display::createDisplay()
	{
		DEBUG_TRACE("Makeshift::Display::createDisplay()");

		DEBUG_INFO("Initializing GLFW...");
		glfwInit();

		// Some basic window hints...
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // We will NEVER have a resizable window, you understand me?!
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

		DEBUG_INFO("Creating Window...");
		m_Window = glfwCreateWindow(1280, 720, "MAKESHIFT", nullptr, nullptr);

		if (!m_Window)
		{
			DEBUG_FATAL("Failed to create Window!");
		}

		glfwMakeContextCurrent(m_Window);

		DEBUG_INFO("Initializing GLAD...");
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			DEBUG_FATAL("Failed to initialize GLAD!");
		}

		glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);

		m_CurrentPolygonMode = GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_DEBUG_OUTPUT);

	}

	void GLAPIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		std::cout << message << std::endl;
	}

	void Display::setDisplaySettings(DisplaySettings settings)
	{

		if (settings.mode != getDisplaySettings().mode)
		{
			//TODO: Window Mode switching
		}

		glfwSetWindowSize(m_Window, settings.width, settings.height);

	}

	DisplaySettings& Display::getDisplaySettings()
	{

		DisplaySettings settings;
		glfwGetWindowSize(m_Window, &settings.width, &settings.height);

		if (glfwGetWindowMonitor(m_Window) == nullptr)
		{
			settings.mode = settings.WINDOWED;
		} 
		else
		{
			settings.mode = settings.FULLSCREEN;
		}

		return settings;

	}

	void Display::closeDisplay()
	{
		DEBUG_TRACE("Makeshift::Display::closeDisplay()");

		DEBUG_INFO("Closing Window...");
		glfwDestroyWindow(m_Window);

	}

	void Display::clear()
	{
		//DEBUG_TRACE("Makeshift::Display::clear()");

		glClear(GL_COLOR_BUFFER_BIT);

	}

	void Display::swapBuffers()
	{
		//DEBUG_TRACE("Makeshift::Display::swapBuffers()");

		glfwSwapBuffers(m_Window);

	}

	void Display::switchPolygonMode()
	{
		if (m_CurrentPolygonMode == GL_FILL) 
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			m_CurrentPolygonMode = GL_LINE;
		}
		else if (m_CurrentPolygonMode == GL_LINE) 
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			m_CurrentPolygonMode = GL_POINT;
		}
		else 
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			m_CurrentPolygonMode = GL_FILL;
		}
	}

	bool Display::isActive()
	{
		//DEBUG_TRACE("Makeshift::Display::isActive()");

		if (glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED))
			return false;

		return !glfwWindowShouldClose(m_Window);

	}

	void Display::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

}
