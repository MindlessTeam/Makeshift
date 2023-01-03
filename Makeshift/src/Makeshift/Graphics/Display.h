// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

struct GLFWwindow;

namespace Makeshift
{

	// Display Settings
	// --------------------------------------------
	// Display Configuration
	struct DisplaySettings
	{
		enum WindowMode
		{
			WINDOWED,
			FULLSCREEN
		}; // Since glfw automatically creates a borderless fulscreen window
		// when possible, this could (should perhaps) be represented by a bool...

		int width, height; // Vec2 maybe?
		WindowMode mode;
	};

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
		void closeDisplay();

		void clear();
		void swapBuffers();

		bool isActive();

	public:
		GLFWwindow* getNativeWindow() { return m_Window; }

	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	private:
		GLFWwindow* m_Window;

	};

}