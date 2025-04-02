#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/fmt/ostr.h>

namespace PTOS::Log {

	extern std::shared_ptr<spdlog::logger> coreLogger;
	extern std::shared_ptr<spdlog::logger> appLogger;

	PTOS_API void init(spdlog::level::level_enum coreLevel, spdlog::level::level_enum appLevel, const std::string& appLoggerName);
	PTOS_API void init(const std::string& appLoggerName);
	PTOS_API void init(spdlog::level::level_enum coreLevel, spdlog::level::level_enum appLevel);
	PTOS_API void init();
}

#ifdef PTOS_LOGGING
//Core Logger
#define PTOS_CORE_TRACE(...)       PTOS::Log::coreLogger->trace(__VA_ARGS__)
#define PTOS_CORE_DEBUG(...)       PTOS::Log::coreLogger->debug(__VA_ARGS__)
#define PTOS_CORE_INFO(...)        PTOS::Log::coreLogger->info(__VA_ARGS__)
#define PTOS_CORE_WARN(...)        PTOS::Log::coreLogger->warn(__VA_ARGS__)
#define PTOS_CORE_ERR(...)         PTOS::Log::coreLogger->error(__VA_ARGS__)
#define PTOS_CORE_CRITICAL(...)    PTOS::Log::coreLogger->critical(__VA_ARGS__)

//App Logger
#define PTOS_TRACE(...)            PTOS::Log::appLogger->trace(__VA_ARGS__)
#define PTOS_DEBUG(...)            PTOS::Log::appLogger->debug(__VA_ARGS__)
#define PTOS_INFO(...)             PTOS::Log::appLogger->info(__VA_ARGS__)
#define PTOS_WARN(...)             PTOS::Log::appLogger->warn(__VA_ARGS__)
#define PTOS_ERR(...)              PTOS::Log::appLogger->error(__VA_ARGS__)
#define PTOS_CRITICAL(...)         PTOS::Log::appLogger->critical(__VA_ARGS__)
#else
#define PTOS_CORE_TRACE(...)
#define PTOS_CORE_DEBUG(...)
#define PTOS_CORE_INFO(...)
#define PTOS_CORE_WARN(...)
#define PTOS_CORE_ERR(...)
#define PTOS_CORE_CRITICAL(...)
#define PTOS_TRACE(...)
#define PTOS_DEBUG(...)
#define PTOS_INFO(...)
#define PTOS_WARN(...)
#define PTOS_ERR(...)
#define PTOS_CRITICAL(...)
#endif
