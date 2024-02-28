#pragma once

#include "Figure.h"

#include <QRectF>

class Rectangle
  : public Figure
{
  Q_OBJECT
public:
  Rectangle(QObject *parent = nullptr);
  virtual ~Rectangle();
private:
  QRectF rect;
};
