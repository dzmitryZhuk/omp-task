#include "Logger.h"

#include <iostream>
#include <QFile>
#include <QDateTime>

void Logger::log(const std::string &message)
{
#ifdef LOG
  auto current = QDateTime::currentDateTime();
  std::string messageWithTimestamp = "[";
  messageWithTimestamp += current.toString("yyyy.MM.dd hh:mm:ss.zzz").toStdString();
  messageWithTimestamp += "] " + message;
  std::cout << messageWithTimestamp << std::endl;
#ifdef LOG_TO_FILE
  QString filename = "log.txt";
#ifdef LOG_FILENAME
  filename = LOG_FILENAME;
#endif
  QFile file{filename};
  file.open(QFile::WriteOnly | QFile::Append);
  file.write(messageWithTimestamp.c_str(), messageWithTimestamp.size());
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
