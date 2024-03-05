#pragma once

#include "Figure.h"

#include <QPointF>

class Triangle
  : public Figure
{
public:
  explicit Triangle(QObject *parent = nullptr);
  Triangle(const QPointF &first, const QPointF &second, QObject *parent = nullptr);
  virtual ~Triangle();
  virtual QString className() const override;

  virtual void draw(QPainter *painter) override;
  virtual void move(double dx, double dy) override;
  virtual bool contains(const QPointF &point) const override;
  virtual QPointF center() const override;
  virtual void setFirstPoint(const QPointF &point) override;
  virtual void setSecondPoint(const QPointF &point) override;

protected slots:
  void calculateVertices();

private:
  QPointF p1_;
  QPointF p2_;
  QPointF p3_;
};
