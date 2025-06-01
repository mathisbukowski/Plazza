/*
** EPITECH PROJECT, 2025
** plazza
** File description:
** Logger.cpp
*/

#include "Logger.hpp"

Plazza::Logger &Plazza::Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Plazza::Logger::log(Plazza::LogLevel level, const std::string &className, const std::string &message)
{
    std::lock_guard<std::mutex> lock(_mutex);

    std::string timestamp = getCurrentTimestamp();
    std::string levelStr = getLevelString(level);

    std::string logEntry = "[" + timestamp + "] [" + levelStr + "] [" + className + "] " + message;
    if (_logFile.is_open()) {
        _logFile << logEntry << std::endl;
        _logFile.flush();
    }
    if (level == LogLevel::ERROR || level == LogLevel::WARNING) {
        std::cerr << logEntry << std::endl;
    }
}

void Plazza::Logger::setLogFile(const std::string &filename)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_logFile.is_open()) {
        _logFile.close();
    }
    _logFile.open(filename, std::ios::out | std::ios::trunc);
    if (!_logFile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Plazza::Logger::~Logger()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_logFile.is_open()) {
        _logFile.close();
    }
}

std::string Plazza::Logger::getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string Plazza::Logger::getLevelString(Plazza::LogLevel level)
{
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}