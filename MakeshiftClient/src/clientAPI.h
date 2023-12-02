// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#ifdef CLIENT
#define CLIENT_API __declspec(dllexport)
#else
#define CLIENT_API __declspec(dllimport)
#endif

struct Client
{

	static CLIENT_API void initLog();

	static CLIENT_API void registerEntities();

	static CLIENT_API void renderIMGUI();
	static CLIENT_API void clientMenuItems();

};