#pragma once

#include "Figure.h"

#include <QRectF>

class Rectangle
  : public Figure
{
  Q_OBJECT
public:
  explicit Rectangle(QObject *parent = nullptr);
  Rectangle(const QPointF &first, const QPointF &second, QObject *parent = nullptr);
  virtual ~Rectangle();
  virtual QString className() const override;

  virtual void draw(QPainter *painter) override;
  virtual void move(double dx, double dy) override;
  virtual bool contains(const QPointF &point) const override;
};
