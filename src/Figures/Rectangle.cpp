#include "Rectangle.h"
#include "../Logger.h"

#include <QString>

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
  painter->drawRect(boundingRect_);
}

void Rectangle::move(double dx, double dy)
{
  boundingRect_.translate(dx, dy);
  // draw
}

bool Rectangle::contains(const QPointF &point) const
{
  return boundingRect_.contains(point);
}
