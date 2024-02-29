#pragma once

#include "Figure.h"

#include <QPointF>

class Triangle
  : public Figure
{
public:
    explicit Triangle(QObject *parent = nullptr);
    virtual ~Triangle();
private:
    QPointF p1_;
    QPointF p2_;
    QPointF p3_;
};
