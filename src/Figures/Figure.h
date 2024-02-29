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

  virtual void draw(QPainter *painter) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual bool contains(const QPointF &point) const = 0;
};
