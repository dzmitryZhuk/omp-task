#include "Rectangle.h"

Rectangle::Rectangle(QObject *parent)
  : Figure(parent)
{
}

Rectangle::Rectangle(const QPointF &first, const QPointF &second, QObject *parent)
  : Figure(first, second, parent)
{
  boundingRect_ = QRectF{first, second};
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

void Rectangle::setSecondPoint(const QPointF &point)
{
  boundingRect_.setBottomRight(point);
}
