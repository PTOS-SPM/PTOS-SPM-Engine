#include "Log.h"

namespace PTOS {
	static const char LOGGING_PATTERN[] = "[%T.%f] %n: %^%v%$";

	PTOS_API std::shared_ptr<spdlog::logger> Log::coreLogger;
	PTOS_API std::shared_ptr<spdlog::logger> Log::appLogger;

	void Log::init(spdlog::level::level_enum coreLevel, spdlog::level::level_enum appLevel, const std::string &appLoggerName) {
		spdlog::set_pattern(LOGGING_PATTERN);
		coreLogger = spdlog::stdout_color_mt("ENGINE");
		coreLogger->set_level(coreLevel);
		appLogger = spdlog::stdout_color_mt(appLoggerName);
		appLogger->set_level(appLevel);
		PTOS_CORE_INFO("Started Logging");
	}

	void Log::init(spdlog::level::level_enum coreLevel, spdlog::level::level_enum appLevel) {
		init(coreLevel, appLevel, "APP");
	}

	void Log::init(const std::string& appLoggerName) {
		init(spdlog::level::trace, spdlog::level::trace, appLoggerName);
	}

	void Log::init() {
		init(spdlog::level::trace, spdlog::level::trace, "APP");
	}
}
