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

		static std::string trimTextToFitArea(const std::string& text, float availableSpace, bool reverseTrim = false);

	};

}