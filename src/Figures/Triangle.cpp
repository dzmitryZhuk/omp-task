#include "Triangle.h"
#include "../Logger.h"

Triangle::Triangle(QObject *parent)
  : Figure{parent}
{
}

Triangle::Triangle(const QPointF &first, const QPointF &second, QObject *parent)
{
  boundingRect_ = QRectF{first, second};
}

Triangle::~Triangle()
{
}

void Triangle::draw(QPainter *painter)
{
  QPolygonF triangle;
  triangle << p1_ << p2_ << p3_;
  painter->drawPolygon(triangle);
  Logger::log(QString(metaObject()->className()) + " <" +
              QString::number(lastEdited_) + "> drawing with bounding rect x<" +
              QString::number(boundingRect_.x()) + "> y <" +
              QString::number(boundingRect_.y()) + "> width <" +
              QString::number(boundingRect_.width()) + "> height <" +
              QString::number(boundingRect_.height()) + ">");
}

void Triangle::move(double dx, double dy)
{
  p1_.rx() += dx;
  p1_.ry() += dy;
  p2_.rx() += dx;
  p2_.ry() += dy;
  p3_.rx() += dx;
  p3_.ry() += dy;
}

bool Triangle::contains(const QPointF &point) const
{
  QPolygonF polygon;
  polygon << p1_ << p2_ << p3_;
  return polygon.containsPoint(point, Qt::OddEvenFill);
}

void Triangle::setFirstPoint(const QPointF &point)
{
  Figure::setFirstPoint(point);
  calculateVertices();
}

void Triangle::setSecondPoint(const QPointF &point)
{
  Figure::setSecondPoint(point);
  calculateVertices();
}

void Triangle::calculateVertices()
{
  p1_ = boundingRect_.bottomLeft();
  p3_ = boundingRect_.bottomRight();
  auto middle = (boundingRect_.right() - boundingRect_.left()) / 2 + boundingRect_.left();
  p2_ = QPointF{middle, boundingRect_.top()};
}
