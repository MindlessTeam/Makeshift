// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace MakeshiftEditor
{

	// Editor Window
	// ----------------------------------------------
	// Base Class for all Editor Windows
	struct EditorWindow
	{

		virtual std::string getTitle() = 0;
		virtual void renderIMGUI() = 0;

		// EditorWindow::setEnabled()
		// ------------------------------------------
		// Sets the windows state.
		//
		//Parameters:
		// - enabled: target window state
		void setEnabled(bool enabled) { m_Enabled = enabled; }

		// EditorWindow::getEnabled()
		// ------------------------------------------
		//Returns:
		// - the window state
		bool getEnabled() { return m_Enabled; }

	protected:
		bool m_Enabled;

	};

}