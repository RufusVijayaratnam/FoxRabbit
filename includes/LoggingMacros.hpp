#ifndef LOGGINGMACROS_HPP
#define LOGGINGMACROS_HPP
#include "Logger.hpp"

#ifdef DEBUG
#define LOG_DEBUG(message) \
    do { \
        std::ostringstream oss; \
        oss << "[DEBUG] " << __FILE__ << ":" << __LINE__ << " " << message; \
        Logger::getInstance().log(oss.str()); \
    } while (0)

#define LOG_INFO(message) \
    do { \
        std::ostringstream oss; \
        oss << "[INFO] " << __FILE__ << ":" << __LINE__ << " " << message; \
        Logger::getInstance().log(oss.str()); \
    } while (0)

#define LOG_WARN(message) \
    do { \
        std::ostringstream oss; \
        oss << "[WARN] " << __FILE__ << ":" << __LINE__ << " " << message; \
        Logger::getInstance().log(oss.str()); \
    } while (0)

#define LOG_ERROR(message) \
    do { \
        std::ostringstream oss; \
        oss << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << message; \
        Logger::getInstance().log(oss.str()); \
    } while (0)
#else
#define LOG_DEBUG(message) do { } while (0)
#define LOG_INFO(message)  do { } while (0)
#define LOG_WARN(message)  do { } while (0)
#define LOG_ERROR(message) do { } while (0)
#endif // DEBUG

#endif // !LOGGINGMACROS_HPP
