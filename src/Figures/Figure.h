#pragma once

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QRectF>

class Figure
  : public QObject
{
  Q_OBJECT
public:
  explicit Figure(QObject *parent = nullptr);
  Figure(const QPointF &first, const QPointF &second, QObject *parent = nullptr);
  virtual ~Figure();

  virtual void draw(QPainter *painter) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual bool contains(const QPointF &point) const = 0;
  virtual void setFirstPoint(const QPointF &point);
  virtual void setSecondPoint(const QPointF &point);
protected:
  QRectF boundingRect_;
  // id = last time used        // TODO: realize id of figure
};
