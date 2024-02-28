#pragma once

#include <QObject>

class Figure : public QObject
{
  Q_OBJECT
public:
  explicit Figure(QObject *parent = nullptr);
  virtual ~Figure();
};