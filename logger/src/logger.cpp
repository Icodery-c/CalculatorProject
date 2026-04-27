#include "logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace logger {

class Logger::Impl { public: std::shared_ptr<spdlog::logger> spd; };

Logger::Logger() : impl(std::make_unique<Impl>()) {

    impl->spd = spdlog::stdout_color_mt("calculator");
    impl->spd->set_pattern("[%H:%M:%S] [%^%l%$] %v");
    impl->spd->set_level(spdlog::level::debug);
}

Logger& Logger::Initialize() {

    static Logger logger;
    return logger;
}

void Logger::trace   (const std::string& msg) { impl->spd->trace(msg);    }

void Logger::debug   (const std::string& msg) { impl->spd->debug(msg);    }

void Logger::info    (const std::string& msg) { impl->spd->info(msg);     }

void Logger::warn    (const std::string& msg) { impl->spd->warn(msg);     }

void Logger::error   (const std::string& msg) { impl->spd->error(msg);    }

void Logger::critical(const std::string& msg) { impl->spd->critical(msg); }

}