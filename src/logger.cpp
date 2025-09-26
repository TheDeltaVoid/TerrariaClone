#include "logger.h"

Logger::Logger() {};

void Logger::_log(std::string text, std::string level, std::string color_start, std::string color_end) {
    std::string out = color_start.append("%s: %s\n").append(color_end);
    printf(out.c_str(), level.c_str(), text.c_str());
}

void Logger::log_info(std::string text) {
    _log(text, "INFO", "\033[32m");
}

void Logger::log_warning(std::string text) {
    _log(text, "WARNING", "\033[33m");
}

void Logger::log_error(std::string text) {
    _log(text, "ERROR", "\033[31m");
}
