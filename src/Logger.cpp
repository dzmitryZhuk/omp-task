#include "Logger.h"

#include <iostream>

void Logger::log(const char *message)
{
  Logger::log(std::string{message});
}

void Logger::log(std::string message)
{
  std::cout << message << std::endl;
}
