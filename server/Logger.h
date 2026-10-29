#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    Logger(const std::string& logFile);
    ~Logger();
    
    void logError(const std::string& severity, const std::string& message);
    
private:
    std::ofstream logFile;
    
    std::string getCurrentTime() const;
};
