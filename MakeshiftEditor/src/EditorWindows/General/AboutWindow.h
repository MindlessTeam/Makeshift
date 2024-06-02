// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "EditorWindows/EditorWindow.h"

namespace MakeshiftEditor
{

	// About Window
	// ----------------------------------------------
	// A simple about window to show some basic
	// info about Makeshift.
	struct AboutWindow : public EditorWindow
	{

		std::string getTitle() override
		{
			return std::string("About");
		}

		void renderIMGUI() override;

	};

}