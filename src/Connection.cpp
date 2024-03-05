#include "Connection.h"

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

Figure *Connection::getFirstFigure() const
{
  return firstFigure_;
}

Figure * Connection::getSecondFigure() const
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
