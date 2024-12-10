// Logger.h
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>
#include <mutex>
#include <sstream>
#include <chrono>

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

    /**
     * @brief Gets a formatted date time string
     *
     * @return Date time string formated as '[Y-m-d H:M:S]'
     */
    std::string dateTimeStr() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm utc_tm = *std::gmtime(&in_time_t);
        std::tm local_tm = *std::localtime(&in_time_t);
        std::ostringstream oss;
        oss << std::put_time(&local_tm, "[%Y-%m-%d %H:%M:%S]");
        return oss.str();
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
