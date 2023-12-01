#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace PTOS {
	class PTOS_API Log {
	public:
		static void init(spdlog::level::level_enum coreLevel, spdlog::level::level_enum appLevel, const std::string &appLoggerName);
		static void init(const std::string &appLoggerName);
		static void init(spdlog::level::level_enum coreLevel, spdlog::level::level_enum appLevel);
		static void init();
		static inline std::shared_ptr<spdlog::logger>& getCoreLogger(void) { return coreLogger; }
		static inline std::shared_ptr<spdlog::logger>& getAppLogger(void) { return appLogger; }

	//should not be instantiated
	private:

		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> appLogger;

		Log() {}
		~Log() {}
	};
}

//Core Logger
#define PTOS_CORE_TRACE(...)       ::PTOS::Log::getCoreLogger()->trace(__VA_ARGS__)
#define PTOS_CORE_DEBUG(...)       ::PTOS::Log::getCoreLogger()->debug(__VA_ARGS__)
#define PTOS_CORE_INFO(...)        ::PTOS::Log::getCoreLogger()->info(__VA_ARGS__)
#define PTOS_CORE_WARN(...)        ::PTOS::Log::getCoreLogger()->warn(__VA_ARGS__)
#define PTOS_CORE_ERR(...)         ::PTOS::Log::getCoreLogger()->error(__VA_ARGS__)
#define PTOS_CORE_CRITICAL(...)    ::PTOS::Log::getCoreLogger()->critical(__VA_ARGS__)

//App Logger
#define PTOS_TRACE(...)            ::PTOS::Log::getAppLogger()->trace(__VA_ARGS__)
#define PTOS_DEBUG(...)            ::PTOS::Log::getAppLogger()->debug(__VA_ARGS__)
#define PTOS_INFO(...)             ::PTOS::Log::getAppLogger()->info(__VA_ARGS__)
#define PTOS_WARN(...)             ::PTOS::Log::getAppLogger()->warn(__VA_ARGS__)
#define PTOS_ERR(...)              ::PTOS::Log::getAppLogger()->error(__VA_ARGS__)
#define PTOS_CRITICAL(...)         ::PTOS::Log::getAppLogger()->critical(__VA_ARGS__)
