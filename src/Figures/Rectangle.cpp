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

  auto x = QString::number(boundingRect_.x());
  auto y = QString::number(boundingRect_.y());
  auto width = QString::number(boundingRect_.width());
  auto height = QString::number(boundingRect_.height());
  Logger::log("Rectangle " /*+ id*/ +                       // TODO: realize id
                        x.toStdString() + " " +
                        y.toStdString() + " " +
                        width.toStdString() + " " +
                        height.toStdString() + " ");
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
