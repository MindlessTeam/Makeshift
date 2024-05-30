// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Log.h"

#include "Makeshift/Utility/FileSystem.h"

#include <iostream>
#include <exception>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/callback_sink.h>
#include <spdlog/formatter.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/fmt/fmt.h>

#include <memory>

#include <iostream>

#include <glad/glad.h>

namespace Makeshift
{

	std::shared_ptr<spdlog::logger> Log::s_Logger;
	Event<std::string> Log::onLogEvent;

	void Log::init()
	{

		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(FileLocations::logLocation() + "makeshift.log", true);
		auto callbackSink = std::make_shared<spdlog::sinks::callback_sink_mt>(logCallback);


		spdlog::sinks_init_list sinkList = { fileSink, consoleSink, callbackSink };

		s_Logger = spdlog::get("MAKESHIFT");
		if (!s_Logger)
		{
			s_Logger = std::make_shared<spdlog::logger>("MAKESHIFT", sinkList.begin(), sinkList.end());
			spdlog::register_logger(s_Logger);
		}
		s_Logger->set_pattern("%^[%L]%$: %v"); // e.g. [I]: Lorem ipsum

		s_Logger->set_level(spdlog::level::trace);
		callbackSink->set_level(spdlog::level::info);

#ifdef CFG_DEBUG || CFG_PRERELEASE
		s_Logger->log(spdlog::level::info, "SPDLOG initialized!");
#endif

	}

	void Log::logCallback(const spdlog::details::log_msg& msg)
	{
		spdlog::memory_buf_t formatted;
		spdlog::pattern_formatter pattern_formatter = spdlog::pattern_formatter ("[%L]: %v");
		pattern_formatter.format(msg, formatted);

		std::string formatted_message(formatted.data(), formatted.size());

		onLogEvent.trigger(formatted_message);
	}

}
