// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

#include "EditorWindows/EditorWindow.h"

namespace MakeshiftEditor
{

	struct $itemname$ : public EditorWindow
	{

		std::string getTitle() override
		{
			return "$itemname$";
		}

		void renderIMGUI() override;

	private: // Values

	};

}