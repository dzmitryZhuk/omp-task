#include "Triangle.h"

Triangle::Triangle(QObject *parent)
  : Figure{parent}
{
}

Triangle::Triangle(const QPointF &p1, const QPointF &p2, const QPointF &p3, QObject *parent)
  : Figure{parent}
  , p1_(p1)
  , p2_(p2)
  , p3_(p3)
{
}

Triangle::~Triangle()
{
}

void Triangle::draw(QPainter *painter)
{
  QPolygonF triangle;
  triangle << p1_ << p2_ << p3_;
  painter->drawPolygon(triangle);
}

void Triangle::move(double dx, double dy)
{
  p1_.rx() += dx;
  p1_.ry() += dy;
  p2_.rx() += dx;
  p2_.ry() += dy;
  p3_.rx() += dx;
  p3_.ry() += dy;
  // draw
}

bool Triangle::contains(const QPointF &point) const
{
  QPolygonF polygon;
  polygon << p1_ << p2_ << p3_;
  return polygon.containsPoint(point, Qt::OddEvenFill);
}
