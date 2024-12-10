#ifndef LOGGINGMACROS_HPP
#define LOGGINGMACROS_HPP
#include "Logger.hpp"

#ifdef DEBUG
#define LOG_DEBUG(message) \
    do { \
        Logger& logger = Logger::getInstance(); \
        std::ostringstream oss; \
        oss << logger.dateTimeStr() << "[DEBUG] " << __FILE__ << ":" << __LINE__ << " " << message; \
        logger.log(oss.str()); \
    } while (0)

#define LOG_INFO(message) \
    do { \
        std::ostringstream oss; \
        Logger& logger = Logger::getInstance(); \
        oss << logger.dateTimeStr() << "[INFO] " << __FILE__ << ":" << __LINE__ << " " << message; \
        logger.log(oss.str()); \
    } while (0)

#define LOG_WARN(message) \
    do { \
        Logger& logger = Logger::getInstance(); \
        std::ostringstream oss; \
        oss << logger.dateTimeStr() << "[WARN] " << __FILE__ << ":" << __LINE__ << " " << message; \
        logger.log(oss.str()); \
    } while (0)

#define LOG_ERROR(message) \
    do { \
        Logger& logger = Logger::getInstance(); \
        std::ostringstream oss; \
        oss << logger.dateTimeStr() << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << message; \
        logger.log(oss.str()); \
    } while (0)
#else
#define LOG_DEBUG(message) do { } while (0)
#define LOG_INFO(message)  do { } while (0)
#define LOG_WARN(message)  do { } while (0)
#define LOG_ERROR(message) do { } while (0)
#endif // DEBUG

#endif // !LOGGINGMACROS_HPP
