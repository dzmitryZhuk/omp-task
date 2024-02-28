#pragma once

#include <QObject>
#include <QPainter>
#include <QPointF>

class Figure
  : public QObject
{
  Q_OBJECT
public:
  explicit Figure(QObject *parent = nullptr);
  virtual ~Figure();

  virtual void draw(QPainter *painter) const = 0;
  virtual void move(double dx, double dy) const = 0;
  virtual void contains(const QPointF &point) const = 0;
};