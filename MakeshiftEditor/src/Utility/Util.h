// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace MakeshiftEditor
{

	struct Util
	{

		// Util::trimTextToFitArea()
		// -----------------------------------------
		// Trims text to fit in an ImGui area.
		//
		// Parameters:
		// - text: The text to trim
		// - availableSpace: The available Space of the ImGui area
		// - reverseTrim: Whether to trim from the back or front (normal: trimmedText... | reverse: ...trimmedText)
		//
		// Returns:
		// - The text trimmed to an area of size x (or the original text if no trimming was necessary)
		static std::string trimTextToFitArea(const std::string& text, float availableSpace, bool reverseTrim = false);

		// Util::getRequiredVerticalTextSize()
		// -----------------------------------------
		// Calculates the amount of vertical space a 
		// certain amount of lines require to be
		// displayed.
		//
		// Parameters:
		// - lines: The Amount of lines to display
		//
		// Returns:
		// - Amount of vertical window space required to display x amount of lines
		static float getRequiredVerticalTextSize(int lines, bool icon = false);

	};

}