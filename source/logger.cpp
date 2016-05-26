#include "logger.h"

#include <iostream>

namespace ot
{
    Logger *Logger::instance = NULL;

    Logger::Logger()
    {
        instance = NULL;
    }


    Logger::~Logger()
    {

    }


    Logger *Logger::getInstance()
    {
        if (instance == NULL)
        {
            instance = new Logger();
        }
        return instance;
    }


    void Logger::error(std::string message)
    {
        std::cout << "error: " << message;
    }

    void Logger::warning(std::string message)
    {
        std::cout << "warning: " << message;
    }

    void Logger::into(std::string message)
    {
        std::cout << "info: " << message;
    }

    void Logger::debug(std::string message)
    {
        std::cout << "debug: " << message;
    }

    void Logger::debug(std::string message, int level)
    {
        std::cout << "debug[" << level << "]: " << message;
    }

    void Logger::timeInfo(std::string message, time_t duration)
    {
        std::cout << "info time: " << duration;
    }

    void Logger::timeDebug(std::string message, time_t duration)
    {
        std::cout << "debug time: " << duration;
    }

    void Logger::timeDebug(std::string message, time_t duration, int level)
    {
        std::cout << "debug[" << level << "] time: " << duration;
    }

}



