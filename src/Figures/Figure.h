#pragma once

#include "../config.h"

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QRectF>
#include <QDataStream>
#include <QString>

class Figure
  : public QObject
{
  Q_OBJECT
public:
  explicit Figure(QObject *parent = nullptr);
  Figure(const QPointF &first, const QPointF &second, QObject *parent = nullptr);
  Figure(const QRectF &boundingRect, QObject *parent = nullptr);
  virtual ~Figure();
  virtual QString className() const = 0;
  friend QDataStream &operator<<(QDataStream &out, const Figure *figure);

  virtual void draw(QPainter *painter) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual bool contains(const QPointF &point) const = 0;
  virtual QPointF center() const;

public slots:
  virtual void setFirstPoint(const QPointF &point);
  virtual void setSecondPoint(const QPointF &point);
  virtual void setLastEdited(const quint64 &timestamp);
  quint64 lastEdited();

protected:
  QRectF boundingRect_;
  quint64 lastEdited_; // timestamp when last time was edited
  quint64 id_;
};
