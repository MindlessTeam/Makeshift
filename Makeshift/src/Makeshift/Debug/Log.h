// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <memory>
#include <string>

namespace spdlog
{
	struct logger;
}

namespace Makeshift
{

	enum LogLevel
	{
		LEVEL_TRACE,
		LEVEL_INFO,
		LEVEL_WARN,
		LEVEL_ERROR,
		LEVEL_FATAL
	};

	// Log
	// --------------------------------------------
	// Logging System for debugging
	struct Log
	{

		static void init();

		static void log(const std::string& msg);
		static void log(LogLevel level, const std::string& msg);
		static void Log::log(LogLevel level, const std::string& source, const std::string& msg);

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
		static std::shared_ptr<spdlog::logger> s_FileLogger;


	};

}

#ifdef CFG_DEBUG

#elif CFG_PRE_RELEASE

#elif CFG_RELEASE

#endif