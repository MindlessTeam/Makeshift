// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Console.h"

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <Makeshift/Debug/Log.h>

namespace MakeshiftEditor
{

	Console* Console::s_Instance = nullptr;

	void Console::renderIMGUI()
	{

		if (s_Instance == nullptr)
		{
			Makeshift::Log::onLogEvent.subscribe(&Console::onLogAction);
			s_Instance = this;

			
		}

		if (!enabled)
			return;

		ImGui::Begin("Console", &enabled);

		for (auto msg : m_LogMessages)
		{
			ImGui::Text(msg.c_str());
			ImGui::Separator();
		}

		ImGui::End();

	}

	void Console::addToLog(const std::string& message)
	{

		m_LogMessages.push_back(message);

	}

	void Console::onLogAction(std::string message)
	{
		Console::getInstance()->addToLog(message);
	}

}