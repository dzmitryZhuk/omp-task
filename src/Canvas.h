#pragma once

#include "Figures/Figure.h"
#include "Connection.h"
#include "config.h"

#include <optional>
#include <QWidget>
#include <QList>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPair>

class Canvas
  : public QWidget
{
  Q_OBJECT
public:
  explicit Canvas(QWidget *parent = nullptr);
  virtual ~Canvas();

public slots:
  void setRectangleDrawingAction();
  void setTriangleDrawingAction();
  void setEllipseDrawingAction();
  void setConnectingFiguresAction();
  void setMovingFigureAction();
  void setRemovingFigureAction();

public:
  enum class Action
  {
    Nothing = 0,
    DrawRectangle,
    DrawTriange,
    DrawEllipse,
    ConnectFigures,
    MoveFigure,
    RemoveFigure,
  };

protected slots:
  void setFigureDrawing(bool enable = true);
  void setFigureMoving(bool enable = true);
  void setConnectingFigures(bool enable = true);
  void cancelAllActions();

protected:
  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

  QList<Figure *> figures_;
  QList<Connection *> connections_;
  bool isFigureDrawing_;
  bool isFigureMoving_;
  bool isConnectingFigures_;
  Figure *currentFigure_;
  Action currentAction_;
  QPair<std::optional<QPointF>, std::optional<QPointF>> connectionLine_;

private slots:
  // findes figure under point
  // return figure that was last modified if there some figures under point
  // return nothing otherwise
  std::optional<Figure *> figureUnderPoint(const QPointF &point) const;
};
