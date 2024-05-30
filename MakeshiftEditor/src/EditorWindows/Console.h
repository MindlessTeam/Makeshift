// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>
#include <vector>

namespace MakeshiftEditor
{

	//TODO: Console - Currently only a test for the callback
	struct Console
	{

		bool enabled = true;

		void renderIMGUI();

	public:
		void addToLog(const std::string& message);

	private:
		std::vector<std::string> m_LogMessages;

	private: // Values
		static void onLogAction(std::string message);

	public:
		static Console* getInstance() { return s_Instance; }
	private:
		static Console* s_Instance;

	};

}