// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

#include "Makeshift/Core/Event.h"

namespace Makeshift
{

	// Log
	// ---------------------------------------------
	// Logging System for debugging.
	struct Log
	{

		// Log::init()
		// -----------------------------------------
		// Initialises the spdlog-logging library.
		static void init();

		// Log::getLogger()
		// -----------------------------------------
		// Returns a shared_ptr to the current
		// spdlog-logger. Don't call this function
		// directly. Use the Macros!
		static std::shared_ptr<spdlog::logger> getLogger() { return s_Logger; }

		static Event<std::string> onLogEvent;

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;

		static void logCallback(const spdlog::details::log_msg& msg);


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
// Logging is one of the most useful debugging tools in existence, so
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
// 
// DEBUG_INFO:
// DEBUG_INFO is used for anything that we want to be outputted, maybe a 
// value, a property-change or an important event in the game loop.
// 
// DEBUG_WARN:
// Warnings are used for things that do not happen according to plan, but 
// should not affect the experience.
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

// DEBUG_TRACE()
// -----------------------------------------
// Prints a Trace to the log.
// 
// Active in:
// - CFG_DEBUG
// 
//NOTE: Place at the start of a function. (see Log.h for more info!)
#define DEBUG_TRACE(...) Makeshift::Log::getLogger()->log(spdlog::level::trace, __VA_ARGS__);

// DEBUG_INFO()
// -----------------------------------------
// Prints an Info-Statement to the log.
// 
// Active in:
// - CFG_DEBUG
// 
//NOTE: For usecases see Log.h and/or existing code.
#define DEBUG_INFO(...)  Makeshift::Log::getLogger()->log(spdlog::level::info, __VA_ARGS__);

// DEBUG_WARN()
// -----------------------------------------
// Prints a Warning to the log.
// 
// Active in:
// - CFG_DEBUG
// - CFG_PRE_RELEASE
// 
//NOTE: For usecases see Log.h and/or existing code.
#define DEBUG_WARN(...)  Makeshift::Log::getLogger()->log(spdlog::level::warn, __VA_ARGS__);

// DEBUG_ERROR()
// -----------------------------------------
// Prints an Error to the log.
// 
// Active in:
// - CFG_DEBUG
// - CFG_PRE_RELEASE
// - CFG_RELEASE
// 
//NOTE: For usecases see Log.h and/or existing code.
#define DEBUG_ERROR(...) Makeshift::Log::getLogger()->log(spdlog::level::err, __VA_ARGS__);

// DEBUG_FATAL()
// -----------------------------------------
// Throws a Fatal Error.
// WILL CRASH THE PROGRAM!
// 
// Active in:
// - CFG_DEBUG
// - CFG_PRE_RELEASE
// - CFG_RELEASE
// 
//NOTE: Only use where absoluetely necessary! (see Log.h for more Info)
#define DEBUG_FATAL(...) Makeshift::Log::getLogger()->log(spdlog::level::critical, __VA_ARGS__); Makeshift::Log::getLogger()->flush(); throw(std::runtime_error("FATAL ERROR"));

#elif CFG_PRERELEASE

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