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
  Logger::log(QString(metaObject()->className()) + " <" +
            QString::number(lastEdited_) + "> drawing with bounding rect x<" +
            QString::number(boundingRect_.x()) + "> y <" +
            QString::number(boundingRect_.y()) + "> width <" +
            QString::number(boundingRect_.width()) + "> height <" +
            QString::number(boundingRect_.height()) + ">");
}

void Rectangle::move(double dx, double dy)
{
  boundingRect_.translate(dx, dy);
}

bool Rectangle::contains(const QPointF &point) const
{
  return boundingRect_.contains(point);
}
