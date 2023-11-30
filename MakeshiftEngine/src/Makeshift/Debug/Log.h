// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

namespace Makeshift
{

	// Log
	// --------------------------------------------
	// Logging System for debugging.
	struct Log
	{

		static void init();

		static std::shared_ptr<spdlog::logger> getLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;


	};

}

// LOG-LEVELS ----------------------------------------------------------------
//
// Makeshift provides 5 different logging levels, which are taken
// from spdlog's built in log levels:
//  - TRACE
//  - INFO
//  - WARN
//  - ERROR
//  - FATAL
//
// In some build-configurations, only some functions actually result
// in a log:
// 
// A DEBUG build will print ALL log levels. (obviously);
// A PRERELEASE build will print Warning, Errors, and Fatal Errors.
// A RELEASE build will only print Errors and Fatal Errors.
//
// Logging is one of the most useful debugging tools in existance, so
// here are a couple of rules to help decide which log level is 
// necessary.
// 
// I try to stick as close to these rules as possible, however, since
// these aren't set in stone LAWS, but much rather GUIDELINES (as 
// Barbossa would say), following these isn't necessary, but they might
// prove to be of some help.
// 
// DEBUG_TRACE:
// Tracing is something classically done for everything that needs some
// sort of input or value outputted to the console. In Makeshift however,
// that's usually the job of DEBUG_INFO.
// DEBUG_TRACE is therefore used at the start of a function, which helps
// to find out in what function an error occurs in if no other indication is
// given.
// In functions that continously repeat every frame, I'd recommend against
// using a DEBUG_TRACE because it makes things rather un-nice to read.
// 
// DEBUG_INFO:
// DEBUG_INFO is used for anything that we want to be outputted, maybe a 
// value, a property-change or an important event in the game loop.
// 
// DEBUG_WARN:
// Warnings are used for things that do not happen according to plan, but 
// that should not affect the experience.
// 
// DEBUG_ERROR:
// An Error is outputted whenever something did not go to plan that could
// (and probably will) affect the experience.
// 
// DEBUG_FATAL:
// Careful: A fatal error will crash the program!
// Fatal errors are only outputted whenever the error is so severe that a
// crash or a completely ruined experience would be given anyway.
//

#include <iostream>
#include <string>

#ifdef CFG_DEBUG

#define DEBUG_TRACE(...) Makeshift::Log::getLogger()->log(spdlog::level::trace, __VA_ARGS__);

#define DEBUG_INFO(...)  Makeshift::Log::getLogger()->log(spdlog::level::info, __VA_ARGS__);

#define DEBUG_WARN(...)  Makeshift::Log::getLogger()->log(spdlog::level::warn, __VA_ARGS__);

#define DEBUG_ERROR(...) Makeshift::Log::getLogger()->log(spdlog::level::err, __VA_ARGS__);

#define DEBUG_FATAL(...) Makeshift::Log::getLogger()->log(spdlog::level::critical, __VA_ARGS__); Makeshift::Log::getLogger()->flush(); throw(std::runtime_error("FATAL ERROR"));

#elif CFG_PRE_RELEASE

#define DEBUG_TRACE(...)
#define DEBUG_INFO(...)
#define DEBUG_WARN(...)  Makeshift::Log::getLogger()->log(spdlog::level::warn, __VA_ARGS__);
#define DEBUG_ERROR(...) Makeshift::Log::getLogger()->log(spdlog::level::err, __VA_ARGS__);
#define DEBUG_FATAL(...) Makeshift::Log::getLogger()->log(spdlog::level::critical, __VA_ARGS__); Makeshift::Log::getLogger()->flush(); throw(std::runtime_error("FATAL ERROR"));

#elif CFG_RELEASE

#define DEBUG_TRACE(...)
#define DEBUG_INFO(...)
#define DEBUG_WARN(...)
#define DEBUG_ERROR(...) Makeshift::Log::getLogger()->log(spdlog::level::err, __VA_ARGS__);
#define DEBUG_FATAL(...) Makeshift::Log::getLogger()->log(spdlog::level::critical, __VA_ARGS__); Makeshift::Log::getLogger()->flush(); throw(std::runtime_error("FATAL ERROR"));

#endif