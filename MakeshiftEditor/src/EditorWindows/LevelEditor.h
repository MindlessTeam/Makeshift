// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace MakeshiftEditor
{

	struct LevelEditor
	{

		bool enabled = false;

		void renderIMGUI();

	private: 
		int m_CurrentlyInspecting = 0;

	};

}