#pragma once

#include "Figure.h"
#include "Connection.h"

#include <QScrollArea>
#include <QList>

class Canvas
  : public QScrollArea
{
public:
  explicit Canvas(QWidget *parent = nullptr);
  virtual ~Canvas();
protected:
  QList<Figure *> figures;
  QList<Connection *> connections;
};
