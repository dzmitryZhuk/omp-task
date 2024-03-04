#include "Logger.h"

#include <iostream>
#include <QFile>

void Logger::log(const std::string &message)
{
#ifdef LOG
  std::cout << message << std::endl;
#ifdef LOG_TO_FILE
  QString filename = "log.txt";
#ifdef LOG_FILENAME
  filename = LOG_FILENAME;
#endif
  QFile file{filename};
  file.open(QFile::WriteOnly | QFile::Append);
  file.write(message.c_str(), message.size());
  file.write("\n");
#endif
#endif
}

void Logger::log(const char *message)
{
  Logger::log(std::string{message});
}

void Logger::log(const QString &message)
{
  Logger::log(message.toStdString());
}
