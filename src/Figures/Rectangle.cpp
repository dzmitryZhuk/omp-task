#include "Rectangle.h"

Rectangle::Rectangle(QObject *parent)
  : Figure(parent)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(QPainter *painter)
{
  painter->drawRect(rect_);
}

void Rectangle::move(double dx, double dy)
{
  rect_.translate(dx, dy);
  // draw
}

bool Rectangle::contains(const QPointF &point) const
{
  return rect_.contains(point);
}
