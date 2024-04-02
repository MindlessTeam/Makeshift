// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

struct GLFWwindow;

namespace Makeshift
{

	// Display Settings
	// ---------------------------------------------
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
	// (Maybe...)

	// Display
	// ---------------------------------------------
	// Manages the window using GLFW.
	class Display
	{

	public:
		Display() {};
		~Display();

	public:
		// Display::createDisplay()
		// -----------------------------------------
		// Creates a GLFWwindow for displaying
		// the games content. Only call this function
		// once!
		void createDisplay();

		// Display::closeDisplay()
		// -----------------------------------------
		// Closes the currently active GLFWwindow.
		void closeDisplay();

		// Display::clear()
		// -----------------------------------------
		// Clears the buffers. (Currently only the 
		// Color Buffer)
		void clear();

		// Display::swapBuffers()
		// -----------------------------------------
		// Swaps the buffers to present the next frame.
		void swapBuffers();

		// Display::switchPolygonMode()
		// -----------------------------------------
		// Cycles between the three polygon modes
		// provided by OpenGL: 
		// - Fill
		// - Wireframe
		// - Point
		void switchPolygonMode();

		// Display::setDisplaySettings()
		// -----------------------------------------
		// Updates the Display Settings.
		//
		// Parameters:
		// - settings: The settings to update to.
		void setDisplaySettings(DisplaySettings settings);

		// Display::getDisplaySettings()
		// -----------------------------------------
		// Checks the current Display Settings.
		//
		// Returns:
		// - the currently active Display Settings
		DisplaySettings getDisplaySettings();

		// Display::isActive()
		// -----------------------------------------
		// Checks if the window is Active.
		//
		// Returns:
		// - true: window is Active
		// - false: window is NOT Active (:O)
		bool isActive();

	public:
		// Display::getNativeWindow()
		// -----------------------------------------
		// Returns:
		// - a pointer to the currently active window.
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