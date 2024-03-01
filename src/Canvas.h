#pragma once

#include "Figures/Figure.h"
#include "Connection.h"

#include <QScrollArea>
#include <QList>

class Canvas
  : public QScrollArea
{
  Q_OBJECT
public:
  explicit Canvas(QWidget *parent = nullptr);
  virtual ~Canvas();

public slots:
  void setFigureDrawing(bool enable = true);
  void setRectangleDrawingAction();
  void setTriangleDrawingAction();
  void setEllipseDrawingAction();

public:
  enum class Action
  {
    Nothing = 0,
    DrawRectangle,
    DrawTriange,
    DrawEllipse,
  };

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

  QList<Figure *> figures_;
  QList<Connection *> connections_;
  bool isFigureDrawingNow_;
  Figure *currentFigure_;
  Action currentAction_;
};
