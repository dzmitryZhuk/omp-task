#pragma once

#include "Figure.h"

#include <QRectF>

class Rectangle
  : public Figure
{
  Q_OBJECT
public:
  explicit Rectangle(QObject *parent = nullptr);
  virtual ~Rectangle();

  virtual void draw(QPainter *painter) override;
  virtual void move(double dx, double dy) override;
  virtual bool contains(const QPointF &point) const override;
private:
  QRectF rect_;
};
