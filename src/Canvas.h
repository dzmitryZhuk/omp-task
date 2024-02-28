#pragma once

#include "Figure.h"
#include "Connection.h"

#include <QWidget>
#include <QList>

class Canvas
  : public QWidget
{
public:
  explicit Canvas(QWidget *parent = nullptr);
  virtual ~Canvas();
protected:
  QList<Figure *> figures;
  QList<Connection *> connections;
};
