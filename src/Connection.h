#pragma once

#include <QObject>

class Connection
  : public QObject
{
  Q_OBJECT
public:
  explicit Connection(QObject *parent = nullptr);
  virtual ~Connection();
};