#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
    public:
    Logger();

    void log_info(std::string text);
    void log_warning(std::string text);
    void log_error(std::string text);

    void _log(std::string text, std::string level, std::string color_start, std::string color_end = "\033[0m");
};

#endif