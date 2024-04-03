// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Makeshift/Core/Event.h"

namespace Makeshift
{

	class ImGuiRenderer
	{

	public:
		static void initializeImGui();
		static void prepareFrame();
		static void endFrame();
		static void cleanUp();

	public:
		static float getFontSize() { return s_FontSizeDefault * s_UISizeModifier; }
		static float getUISizeModifier() { return s_UISizeModifier; }

		static bool isInitialized() { return s_IsInitialized; }

	public:
		static void doubleUISize();
		static void halfUISize();
		static void setUISize(float size);

		static void applyModifiersBasedOnMonitorResolution(float width, float height);

	private:
		static void updateImGuiStyle();
		static void saveFileToDisk();
		static void loadFileFromDisk();

	private:
		static float s_UISizeModifier;
		static float s_FontSizeDefault;
		static bool s_ResizeRequested;
		static bool s_IsInitialized;

	};

}