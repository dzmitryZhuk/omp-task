#include "Ellipse.h"

Ellipse::Ellipse(QObject *parent)
  : Figure{parent}
{
}

Ellipse::Ellipse(const QRectF &rect, QObject *parent)
  : Figure{rect, parent}
{
}

Ellipse::~Ellipse()
{
}

void Ellipse::draw(QPainter *painter)
{
  painter->drawEllipse(boundingRect_);
}

void Ellipse::move(double dx, double dy)
{
  boundingRect_.translate(dx, dy);
  // draw
}

bool Ellipse::contains(const QPointF &point) const
{
  if (boundingRect_.contains(point))
  {
    auto x = point.x();
    auto y = point.y();
    auto x0 = boundingRect_.center().x();
    auto y0 = boundingRect_.center().y();
    auto a = boundingRect_.width() / 2.0;
    auto b = boundingRect_.height() / 2.0;
    return (((x - x0) * (x - x0)) / (a * a) + ((y - y0) * (y - y0)) / (b * b)) <= 1;
  }
  return false;
}
