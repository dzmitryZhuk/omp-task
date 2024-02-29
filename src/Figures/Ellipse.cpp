#include "Ellipse.h"

Ellipse::Ellipse(QObject *parent)
  : Figure{parent}
{
}

Ellipse::Ellipse(const QRectF &rect, QObject *parent)
  : Figure{parent}
  , rect_(rect)
{
}

Ellipse::~Ellipse()
{
}

void Ellipse::draw(QPainter *painter)
{
  painter->drawEllipse(rect_);
}

void Ellipse::move(double dx, double dy)
{
  rect_.translate(dx, dy);
  // draw
}

bool Ellipse::contains(const QPointF &point) const
{
  if (rect_.contains(point))
  {
    auto x = point.x();
    auto y = point.y();
    auto x0 = rect_.center().x();
    auto y0 = rect_.center().y();
    auto a = rect_.width() / 2.0;
    auto b = rect_.height() / 2.0;
    return (((x - x0) * (x - x0)) / (a * a) + ((y - y0) * (y - y0)) / (b * b)) <= 1;
  }
  return false;
}
