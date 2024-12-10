// Logger.h
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>
#include <mutex>
#include <sstream>

/**
 * @class Logger
 * @brief A singleton logging class, only runs when compiled with DEBUG defined
 *
 */
class Logger {
public:
    /**
     * @brief Get the singleton logger instance
     *
     * @return Singleton logger instance
     */
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    /**
     * @brief Write log message to file. Uses mutex to protect from data race.
     *
     * @param message 
     */
    void log(const std::string& message) {
        std::lock_guard<std::mutex> guard(logMutex);
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }

private:
    std::ofstream logFile;
    std::mutex logMutex;

    Logger() {
        logFile.open("fox_rabbit.log", std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file: app.log");
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

#endif // LOGGER_HPP
