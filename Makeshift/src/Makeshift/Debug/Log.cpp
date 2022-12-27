// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Log.h"

#include "Makeshift/Utility/FileSystem.h"

#include <iostream>
#include <exception>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Makeshift
{

	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::init()
	{

		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(Util::FileLocations::logLocation() + "/log.txt", true);

		spdlog::sinks_init_list sinkList = { fileSink, consoleSink };

		s_Logger = std::make_shared<spdlog::logger>("MAKESHIFT", sinkList.begin(), sinkList.end());

		s_Logger->set_pattern("%^[%L]%$: %v");
#ifdef CFG_DEBUG
		s_Logger->set_level(spdlog::level::trace);
#else
		s_Logger->set_level(spdlog::level::warn);
#endif

		s_Logger->log(spdlog::level::info, "SPDLOG initialized!");

	}

	void Log::log(const std::string& msg)
	{

		s_Logger->log(spdlog::level::info, msg);

	}

	void Log::log(LogLevel level, const std::string& msg)
	{

		switch (level)
		{
		case LogLevel::LEVEL_TRACE:
			s_Logger->log(spdlog::level::trace, msg);
			break;
		case LogLevel::LEVEL_INFO:
			s_Logger->log(spdlog::level::info, msg);
			break;
		case LogLevel::LEVEL_WARN:
			s_Logger->log(spdlog::level::warn, msg);
			break;
		case LogLevel::LEVEL_ERROR:
			s_Logger->log(spdlog::level::err, msg);
			break;
		case LogLevel::LEVEL_FATAL:
			s_Logger->log(spdlog::level::critical, msg);
			s_Logger->flush();
			throw(std::runtime_error("FATAL ERROR!"));
			break;
		}

	}

	void Log::log(LogLevel level, const std::string& source, const std::string& msg)
	{

		switch (level)
		{
		case LogLevel::LEVEL_TRACE:
			s_Logger->log(spdlog::level::trace, source + ": " + msg);
			break;
		case LogLevel::LEVEL_INFO:
			s_Logger->log(spdlog::level::info, source + ": " + msg);
			break;
		case LogLevel::LEVEL_WARN:
			s_Logger->log(spdlog::level::warn, source + ": " + msg);
			break;
		case LogLevel::LEVEL_ERROR:
			s_Logger->log(spdlog::level::err, source + ": " + msg);
			break;
		case LogLevel::LEVEL_FATAL:
			s_Logger->log(spdlog::level::critical, source + ": " + msg);
			s_Logger->flush();
			throw(std::runtime_error("FATAL ERROR!"));
			break;
		}

	}

}
