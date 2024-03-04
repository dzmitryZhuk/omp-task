#pragma once

#include "config.h"

#include <string>
#include <QString>

class Logger
{
public:
  static void log(const char * message);
  static void log(const std::string &message);
  static void log(const QString &message);
};
