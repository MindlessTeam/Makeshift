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
		static float getFontSize() { return fontSizeDefault * UISizeModifier; }
		static float getUISizeModifier() { return UISizeModifier; }

	public:
		static void doubleUISize();
		static void halfUISize();
		static void setUISize(float size);

		static void applyModifiersBasedOnMonitorResolution(float width, float height);

	private:
		static void updateImGuiStyle();

	private:
		static float UISizeModifier;
		static float fontSizeDefault;
		static bool resizeRequested;

	};

}