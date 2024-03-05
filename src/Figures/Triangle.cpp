#include "Triangle.h"
#include "../Logger.h"

Triangle::Triangle(QObject *parent)
  : Figure{parent}
{
}

Triangle::Triangle(const QPointF &first, const QPointF &second, QObject *parent)
  : Figure{first, second, parent}
{
}

Triangle::Triangle(const QRectF &boundingRect, QObject *parent)
  : Figure{boundingRect, parent}
{
}

Triangle::~Triangle()
{
}

QString Triangle::className() const
{
  return QString{"Triangle"};
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
  boundingRect_.translate(dx, dy);
  calculateVertices();
}

bool Triangle::contains(const QPointF &point) const
{
  QPolygonF polygon;
  polygon << p1_ << p2_ << p3_;
  return polygon.containsPoint(point, Qt::OddEvenFill);
}

QPointF Triangle::center() const
{
  auto x = (p1_.x() + p2_.x() + p3_.x()) / 3;
  auto y = (p1_.y() + p2_.y() + p3_.y()) / 3;
  return QPointF{x, y};
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
