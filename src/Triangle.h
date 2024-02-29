#pragma once

#include "Figure.h"

#include <QPointF>

class Triangle
  : public Figure
{
public:
  explicit Triangle(QObject *parent = nullptr);
  Triangle(const QPointF &p1, const QPointF &p2, const QPointF &p3, QObject *parent = nullptr);
  virtual ~Triangle();

  virtual void draw(QPainter *painter) override;
  virtual void move(double dx, double dy) override;
  virtual bool contains(const QPointF &point) const override;
private:
  QPointF p1_;
  QPointF p2_;
  QPointF p3_;
};
