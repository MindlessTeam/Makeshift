// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	class ImGuiRenderer
	{

	public:
		static void initializeImGui();
		static void prepareFrame();
		static void endFrame();
		static void cleanUp();

	};

}