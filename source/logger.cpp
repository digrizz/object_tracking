#include "logger.h"

#include <iostream>

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
void Logger::debug(std::string message)
{
    std::cout << "debug: " << message;
}
void Logger::debug(std::string message, int level)
{
    std::cout << "debug[" << level << "]: " << message;
}



