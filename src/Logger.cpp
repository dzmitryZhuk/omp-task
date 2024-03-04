#include "Logger.h"

#include <iostream>

void Logger::log(const char *message)
{
  Logger::log(std::string{message});
}

void Logger::log(const std::string &message)
{
  std::cout << message << std::endl;
}

void Logger::log(const QString &message)
{
  Logger::log(message.toStdString());
}
