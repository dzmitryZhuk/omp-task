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
  currentFigure_ = new Rectangle{};
  Logger::log("Canvas new Rectangle");
}

void Canvas::setTriangleDrawingAction()
{
  currentAction_ = Action::DrawTriange;
  setFigureDrawing();
  Logger::log("Canvas setting triangle drawing action");
  // currentFigure_ = new Triangle{};
  // Logger::log("Canvas new Triangle");
}

void Canvas::setEllipseDrawingAction()
{
  currentAction_ = Action::DrawEllipse;
  setFigureDrawing();
  Logger::log("Canvas setting ellipse drawing action");
  // currentFigure_ = new Ellipse{};
  // Logger::log("Canvas new Ellipse");
}

void Canvas::setFigureDrawing(bool enable)
{
  isFigureDrawingNow_ = enable;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
  QString xString = QString::number(event->pos().x());
  QString yString = QString::number(event->pos().y());
  Logger::log("Canvas mouse press event at <" + xString.toStdString() + "> <" + yString.toStdString() + ">");
  if (isFigureDrawingNow_)
  {
    switch (currentAction_)
    {
    case Action::DrawRectangle:
      currentFigure_->setFirstPoint(event->pos());
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
  QString xString = QString::number(event->pos().x());
  QString yString = QString::number(event->pos().y());
  Logger::log("Canvas mouse move event at <" + xString.toStdString() + "> <" + yString.toStdString() + ">");
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
