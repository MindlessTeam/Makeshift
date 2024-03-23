// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
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
		}; // Since glfw automatically creates a borderless fullscreen window
		// when possible, this could (should perhaps) be represented by a bool...

		int fullscreenDisplay = 0;

		int width, height; // Vec2 maybe?
		WindowMode mode;
		bool VSync;
	};

	//TODO: Implement Display Settings into Display class

	// Display
	// --------------------------------------------
	// Display handling
	class Display
	{

	public:
		Display() {};
		~Display();

	public:
		void createDisplay();
		void closeDisplay();

		void clear();
		void swapBuffers();

		void switchPolygonMode();

		void setDisplaySettings(DisplaySettings settings);
		DisplaySettings& getDisplaySettings();

		bool isActive();

	public:
		GLFWwindow* getNativeWindow() { return m_Window; }

	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		//TODO: static void monitorCallback();

	private:
		int m_CurrentPolygonMode;

	private:
		GLFWwindow* m_Window;

	};

}