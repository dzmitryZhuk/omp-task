#include "Figure.h"
#include "../Logger.h"

Figure::Figure(QObject *parent)
  : QObject(parent)
{
}

Figure::Figure(const QPointF &first, const QPointF &second, QObject *parent)
  : QObject(parent)
  , boundingRect_(QRectF{first, second})
{
}

Figure::Figure(const QRectF &boundingRect, QObject *parent)
  : QObject(parent)
  , boundingRect_(boundingRect)
{
}

Figure::~Figure()
{
}

void Figure::setFirstPoint(const QPointF &point)
{
  boundingRect_.setTopLeft(point);
}

QPointF Figure::center() const
{
  return boundingRect_.center();
}

void Figure::setSecondPoint(const QPointF &point)
{
  boundingRect_.setBottomRight(point);
}

void Figure::setLastEdited(const quint64 &timestamp)
{
  lastEdited_ = timestamp;
}

quint64 Figure::lastEdited()
{
  return lastEdited_;
}

QDataStream &operator<<(QDataStream &out, const Figure *figure)
{
  Logger::log("Writing to stream figure " + figure->className());
  out << figure->className();
  out << figure->boundingRect_;
  out << figure->lastEdited_;
  return out;
}
