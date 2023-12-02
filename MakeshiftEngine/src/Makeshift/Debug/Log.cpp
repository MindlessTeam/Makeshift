// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Log.h"

#include "Makeshift/Utility/FileSystem.h"

#include <iostream>
#include <exception>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <glad/glad.h>

namespace Makeshift
{

	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::init()
	{

		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(FileLocations::logLocation() + "makeshift.log", true);

		spdlog::sinks_init_list sinkList = { fileSink, consoleSink };

		s_Logger = spdlog::get("MAKESHIFT");
		if (!s_Logger)
		{
			s_Logger = std::make_shared<spdlog::logger>("MAKESHIFT", sinkList.begin(), sinkList.end());
			spdlog::register_logger(s_Logger);
		}
		s_Logger->set_pattern("%^[%L]%$: %v"); // e.g. [I]: Lorem ipsum

		s_Logger->set_level(spdlog::level::trace);

		s_Logger->log(spdlog::level::info, "SPDLOG initialized!");

	}

}
