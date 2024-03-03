#include "Canvas.h"
#include "Figures/Rectangle.h"
#include "Figures/Triangle.h"
#include "Figures/Ellipse.h"
#include "Logger.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QtGlobal>

Canvas::Canvas(QWidget *parent)
  : QWidget/*QScrollArea*/(parent)
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
  setFigureDrawing(true);
  Logger::log("Canvas setting rectangle drawing action");
}

void Canvas::setTriangleDrawingAction()
{
  currentAction_ = Action::DrawTriange;
  setFigureDrawing(true);
  Logger::log("Canvas setting triangle drawing action");
}

void Canvas::setEllipseDrawingAction()
{
  currentAction_ = Action::DrawEllipse;
  setFigureDrawing(true);
  Logger::log("Canvas setting ellipse drawing action");
}

void Canvas::setConnectingFiguresAction()
{
  currentAction_ = Action::ConnectFigures;
  Logger::log("Canvas setting connect action");
}

void Canvas::setMovingFigureAction()
{
  currentAction_ = Action::MoveFigure;
  Logger::log("Canvas setting move action");
}

void Canvas::setRemovingFigureAction()
{
  currentAction_ = Action::RemoveFigure;
  Logger::log("Canvas setting remove action");
}

void Canvas::setFigureDrawing(bool enable)
{
  isFigureDrawing_ = enable;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
  QString xString = QString::number(event->pos().x());
  QString yString = QString::number(event->pos().y());
  Logger::log("Canvas mouse press event at <" + xString.toStdString() + "> <" + yString.toStdString() + ">");

  if (isFigureDrawing_)
  {
    switch (currentAction_) {
      case Action::DrawRectangle:
        currentFigure_ = new Rectangle{this};
        Logger::log("Canvas new Rectangle");
        break;
      case Action::DrawTriange:
        currentFigure_ = new Triangle{this};
        Logger::log("Canvas new Triangle");
        break;
      case Action::DrawEllipse:
        currentFigure_ = new Ellipse{this};
        Logger::log("Canvas new Ellipse");
      default:
        break;
    }
    if (currentFigure_)
    {
      currentFigure_->setFirstPoint(event->pos());
      currentFigure_->setSecondPoint(event->pos());
      figures_.push_back(currentFigure_);
      update();
    }
  }

  switch (currentAction_) {
  case Action::RemoveFigure:
    for (qsizetype i = 0; i < figures_.size(); i++)
    {
      auto item = figures_.at(i);
      if (item->contains(event->pos()))
      {
#if QT_VERSION_MAJOR == 5
        figures_.removeAt(i);
#else
        figures_.remove(i);
#endif
        Logger::log("Canvas remove figure");
        delete item;
      }
    }
    break;
  default:
    break;
  }
  update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
  QString xString = QString::number(event->pos().x());
  QString yString = QString::number(event->pos().y());
  Logger::log("Canvas mouse move event at <" + xString.toStdString() + "> <" + yString.toStdString() + ">");

  if (isFigureDrawing_ && currentFigure_)
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
  Logger::log("Canvas paint event");
  QPainter painter(this/*viewport()*/);
  painter.fillRect(rect(), Qt::white);
  painter.setPen(QColor{Qt::black});
  for (const auto &item : figures_)
  {
    item->draw(&painter);
  }
}
