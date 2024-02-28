#pragma once

#include "Figure.h"

class Rectangle
  : public Figure
{
  Q_OBJECT
public:
  Rectangle(/* args */);
  ~Rectangle();
private:
  QRectF rect;
};
