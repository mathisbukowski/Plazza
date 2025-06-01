/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Logger.hpp
*/

#ifndef PLAZZA_LOGGER_HPP
#define PLAZZA_LOGGER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Plazza {

    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    class Logger {
    public:
        static Logger& getInstance();
        void log(LogLevel level, const std::string& className, const std::string& message);
        void setLogFile(const std::string& filename);
        ~Logger();

    private:
        Logger() = default;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        std::string getCurrentTimestamp();
        std::string getLevelString(LogLevel level);
        std::ofstream _logFile;
        std::mutex _mutex;
    };

#define LOG_DEBUG(className, message) \
        Logger::getInstance().log(LogLevel::DEBUG, className, message)

#define LOG_INFO(className, message) \
        Logger::getInstance().log(LogLevel::INFO, className, message)

#define LOG_WARNING(className, message) \
        Logger::getInstance().log(LogLevel::WARNING, className, message)

#define LOG_ERROR(className, message) \
        Logger::getInstance().log(LogLevel::ERROR, className, message)

}

#endif //PLAZZA_LOGGER_HPP
