// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <imgui/imgui.h>
#include <vector>

namespace MakeshiftEditor
{

	struct TextureEditor
	{

		bool enabled = false;

		void renderIMGUI();

	private: // Values
		std::vector<ImWchar> m_Characters;

		bool m_FlagCreation = false;
		float m_TimeSinceFlag = 0;

	};

}