#include "Canvas.h"
#include "Figures/Rectangle.h"
#include "Figures/Triangle.h"
#include "Figures/Ellipse.h"
#include "Logger.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>

Canvas::Canvas(QWidget *parent)
  : QScrollArea(parent)
  , currentFigure_(nullptr)
  , currentAction_(Action::Nothing)
{
  setFigureDrawing(false);
}

Canvas::~Canvas()
{
}

void Canvas::setRectangleDrawingAction()
{
  currentAction_ = Action::DrawRectangle;
  setFigureDrawing();
  Logger::log("Canvas setting rectangle drawing action");
}

void Canvas::setTriangleDrawingAction()
{
  currentAction_ = Action::DrawTriange;
  setFigureDrawing();
  Logger::log("Canvas setting triangle drawing action");
}

void Canvas::setEllipseDrawingAction()
{
  currentAction_ = Action::DrawEllipse;
  setFigureDrawing();
  Logger::log("Canvas setting ellipse drawing action");
}

void Canvas::setFigureDrawing(bool enable)
{
  isFigureDrawingNow_ = enable;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
  Logger::log("Canvas mouse press event");
  if (isFigureDrawingNow_)
  {
    switch (currentAction_)
    {
    case Action::DrawRectangle:
      currentFigure_ = new Rectangle{event->pos(), event->pos()};
      Logger::log("Canvas new Rectangle");
      break;
    
    default:
      break;
    }
    if (currentFigure_)
    {
      figures_.append(currentFigure_);
    }
  }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
  Logger::log("Canvas mouse move event");
  if (isFigureDrawingNow_ && currentFigure_)
  {
    currentFigure_->setSecondPoint(event->pos());
    update();
  }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
  Logger::log("Canvas mouse release event");
  currentAction_ = Action::Nothing;
  currentFigure_ = nullptr;
  update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
  // Logger::log("Canvas paint event");
  QPainter painter(viewport());
  painter.setPen(QColor{Qt::black});
  painter.setBrush(QColor{Qt::black});
  for (const auto &item : figures_)
  {
    item->draw(&painter);
  }
  painter.drawRect(20,40,90,110);
}
