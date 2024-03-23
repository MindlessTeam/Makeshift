// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#ifdef MAKESHIFT_IMGUI
#pragma message("IMGUI_ENABLED")
#define IMGUI
#endif

#ifdef MAKESHIFT_EDITOR
#pragma message("EDITOR_ENABLED")
#define EDITOR
#endif

#include "Core/Engine.h"
#include "Core/Event.h"