#include "Connection.h"
#include "Logger.h"

Connection::Connection(QObject *parent)
  : QObject(parent)
  , firstFigure_(nullptr)
  , secondFigure_(nullptr)
{
}

Connection::Connection(Figure *firstFigure, Figure *secondFigure, QObject *parent)
  : QObject(parent)
  , firstFigure_(firstFigure)
  , secondFigure_(secondFigure)
{
}

Connection::~Connection()
{
}

void Connection::draw(QPainter *painter) const
{
  if (!firstFigure_ || !secondFigure_)
  {
    return;
  }

  auto firstPoint = firstFigure_->center();
  auto secondPoint = secondFigure_->center();
  painter->drawLine(firstPoint, secondPoint);
}

bool Connection::containsFigure(const Figure * figure) const
{
  return figure == firstFigure_ || figure == secondFigure_;
}

Figure *Connection::firstFigure() const
{
  return firstFigure_;
}

Figure * Connection::secondFigure() const
{
  return secondFigure_;
}

void Connection::setFirstFigure(Figure *figure)
{
  firstFigure_ = figure;
}

void Connection::setSecondFigure(Figure *figure)
{
  secondFigure_ = figure;
}

QDataStream &operator<<(QDataStream &out, const Connection *conection)
{
  Logger::log("Writing to stream connection ");
  out << conection->firstFigure()->lastEdited();
  out << conection->secondFigure()->lastEdited();
  return out;
}
