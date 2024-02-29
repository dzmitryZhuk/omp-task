#include "Figure.h"

Figure::Figure(QObject *parent)
  : QObject(parent)
{
}

Figure::Figure(const QPointF &first, const QPointF &second, QObject *parent)
  : QObject(parent)
  , boundingRect_(QRectF{first, second})
{
}

Figure::~Figure()
{
}
