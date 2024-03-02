#pragma once

#include "Figure.h"

#include <QRectF>

class Ellipse : public Figure
{
public:
  explicit Ellipse(QObject *parent = nullptr);
  Ellipse(const QRectF &rect, QObject *parent = nullptr);
  virtual ~Ellipse();

  virtual void draw(QPainter *painter) override;
  virtual void move(double dx, double dy) override;
  virtual bool contains(const QPointF &point) const override;
};
