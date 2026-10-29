#include "Logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>
Logger::Logger(const std::string& logFile) {
    this->logFile.open(logFile, std::ios::app);
    if (!this->logFile.is_open()) {
        throw std::runtime_error("Cannot open log file: " + logFile);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::logError(const std::string& severity, const std::string& message) {
    logFile << getCurrentTime() << " [" << severity << "] " << message << std::endl;
    logFile.flush();
}

std::string Logger::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
