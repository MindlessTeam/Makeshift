// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
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
		//TODO
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
		GLFWwindow* m_Window;

	};

}