#pragma once

#include <string>

class Logger
{
public:
  static void log(const char * message);
  static void log(std::string message);
};
