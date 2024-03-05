#include "Canvas.h"
#include "Figures/Rectangle.h"
#include "Figures/Triangle.h"
#include "Figures/Ellipse.h"
#include "Logger.h"

#include <QPen>
#include <QBrush>
#include <QtGlobal>

Canvas::Canvas(QWidget *parent)
  : QWidget(parent)
  , currentFigure_(nullptr)
  , currentAction_(Action::Nothing)
{
  setFigureDrawing(false);
  setFigureMoving(false);
}

Canvas::~Canvas()
{
}

void Canvas::setRectangleDrawingAction()
{
  currentAction_ = Action::DrawRectangle;
  setFigureDrawing(true);
  setFigureMoving(false);
  setConnectingFigures(false);
  Logger::log("Canvas setting rectangle drawing action");
}

void Canvas::setTriangleDrawingAction()
{
  currentAction_ = Action::DrawTriange;
  setFigureDrawing(true);
  setFigureMoving(false);
  setConnectingFigures(false);
  Logger::log("Canvas setting triangle drawing action");
}

void Canvas::setEllipseDrawingAction()
{
  currentAction_ = Action::DrawEllipse;
  setFigureDrawing(true);
  setFigureMoving(false);
  setConnectingFigures(false);
  Logger::log("Canvas setting ellipse drawing action");
}

void Canvas::setConnectingFiguresAction()
{
  currentAction_ = Action::ConnectFigures;
  setFigureDrawing(false);
  setFigureMoving(false);
  setConnectingFigures(true);
  Logger::log("Canvas setting connect action");
}

void Canvas::setMovingFigureAction()
{
  currentAction_ = Action::MoveFigure;
  setFigureMoving(true);
  setFigureDrawing(false);
  setConnectingFigures(false);
  Logger::log("Canvas setting move action");
}

void Canvas::setRemovingFigureAction()
{
  currentAction_ = Action::RemoveFigure;
  setFigureDrawing(false);
  setFigureMoving(false);
  setConnectingFigures(false);
  Logger::log("Canvas setting remove action");
}

void Canvas::setFigureDrawing(bool enable)
{
  isFigureDrawing_ = enable;
}

void Canvas::setFigureMoving(bool enable)
{
  isFigureMoving_ = enable;
  setMouseTracking(enable);
}

void Canvas::setConnectingFigures(bool enable)
{
  isConnectingFigures_ = enable;
}

void Canvas::cancelAllActions()
{
  currentAction_ = Action::Nothing;
  setFigureDrawing(false);
  setFigureMoving(false);
  setConnectingFigures(false);
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    Logger::log("Key Esc pressed");
    cancelAllActions();
    if (currentFigure_)
    {
      if (isFigureDrawing_)
      {
        delete currentFigure_;
      }
      currentFigure_ = nullptr;
    }
  }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
  QString xString = QString::number(event->pos().x());
  QString yString = QString::number(event->pos().y());
  Logger::log("Canvas mouse press event at <" + xString.toStdString() + "> <" + yString.toStdString() + ">");

  if (event->button() == Qt::MouseButton::LeftButton)
  {
    Logger::log("Mouse left button pressed");
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
        currentFigure_->setLastEdited(event->timestamp());
        update();
      }
    }

    switch (currentAction_) {
    case Action::RemoveFigure:
      for (qsizetype i = 0; i < figures_.size(); i++)
      {
        // make array of figures that contain event->pos()
        // remove figure with biggest timestamp (lastEdited)
        auto item = figures_.at(i);
        if (item->contains(event->pos()))
        {
#if QT_VERSION_MAJOR == 5
          figures_.removeAt(i);
#else
          figures_.remove(i);
#endif
          delete item;
          Logger::log("Canvas remove figure");
        }
      }
      break;
    case Action::MoveFigure:
      for (qsizetype i = 0; i < figures_.size(); i++)
      {
        // make array of figures that contain event->pos()
        // currentFigure is figure from last step (with biggest timestamp (lastEdited))
        auto item = figures_.at(i);
        if (item->contains(event->pos()))
        {
          currentFigure_ = item;
          Logger::log("Canvas move figure");
        }
      }
      break;
    default:
      break;
    }
    update();
  }
  if (event->button() == Qt::MouseButton::RightButton)
  {
    Logger::log("Mouse right button pressed");
    cancelAllActions();
    if (currentFigure_)
    {
      if (isFigureDrawing_)
      {
        delete currentFigure_;
      }
      currentFigure_ = nullptr;
    }
  }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
  QString xString = QString::number(event->pos().x());
  QString yString = QString::number(event->pos().y());
  Logger::log("Canvas mouse move event at <" + xString.toStdString() + "> <" + yString.toStdString() + ">");

  if (isFigureDrawing_ && currentFigure_)
  {
    currentFigure_->setSecondPoint(event->pos());
    currentFigure_->setLastEdited(event->timestamp());
    update();
  }

  static decltype(event->pos()) lastPos;
  if (isFigureMoving_ && currentFigure_)
  {
    auto currentPos = event->pos();
    auto dx = currentPos.x() - lastPos.x();
    auto dy = currentPos.y() - lastPos.y();
    Logger::log("Canvas make figure move to dx " + QString::number(dx) + " dy " + QString::number(dy));
    currentFigure_->move(dx, dy);
    currentFigure_->setLastEdited(event->timestamp());
    update();
  }
  lastPos = event->pos();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
  Logger::log("Canvas mouse release event");
  if (isFigureDrawing_ && currentFigure_)
  {
    figures_.push_back(currentFigure_);
  }
  currentFigure_ = nullptr;
  cancelAllActions();
  update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
  Logger::log("Canvas paint event");
  QPainter painter(this);
  painter.fillRect(rect(), Qt::white);
  painter.setPen(QColor{Qt::black});
  for (const auto &item : figures_)
  {
    item->draw(&painter);
  }
  if (currentFigure_)
  {
    currentFigure_->draw(&painter);
  }
}
