#pragma once

#include "Figure.h"

#include <QRectF>

class Ellipse : public Figure
{
public:
    explicit Ellipse(QObject *parent = nullptr);
    virtual ~Ellipse();
};
