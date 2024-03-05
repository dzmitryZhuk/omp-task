#include "Ellipse.h"
#include "../Logger.h"

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

QString Ellipse::className() const
{
  return QString{"Ellipse"};
}

void Ellipse::draw(QPainter *painter)
{
  painter->drawEllipse(boundingRect_);
  Logger::log(QString(metaObject()->className()) + " <" +
                QString::number(lastEdited_) + "> drawing with bounding rect x<" +
                QString::number(boundingRect_.x()) + "> y <" +
                QString::number(boundingRect_.y()) + "> width <" +
                QString::number(boundingRect_.width()) + "> height <" +
                QString::number(boundingRect_.height()) + ">");
}

void Ellipse::move(double dx, double dy)
{
  boundingRect_.translate(dx, dy);
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
