#pragma once

#include "config.h"
#include "Figures/Figure.h"

#include <QObject>

class Connection
  : public QObject
{
  Q_OBJECT
public:
  explicit Connection(QObject *parent = nullptr);
  Connection(Figure *firstFigure, Figure *secondFigure, QObject *parent = nullptr);
  virtual ~Connection();

  virtual void draw(QPainter *painter) const;
  bool containsFigure(const Figure *figure) const;
  Figure * getFirstFigure() const;
  Figure * getSecondFigure() const;

public slots:
  void setFirstFigure(Figure *figure);
  void setSecondFigure(Figure *figure);

protected:
  Figure *firstFigure_;
  Figure *secondFigure_;
};
