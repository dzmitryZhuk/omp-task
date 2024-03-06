#include "Canvas.h"
#include "Figures/Rectangle.h"
#include "Figures/Triangle.h"
#include "Figures/Ellipse.h"
#include "Logger.h"

#include <set>
#include <algorithm>
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

void Canvas::setFiguresAndConnections(const QList<Figure *> &figures, const QList<Connection *> &connections)
{
  figures_.clear();
  connections_.clear();
  figures_ = figures;
  connections_ = connections;
}

void Canvas::setFigures(const QList<Figure *> &figures)
{
  figures_.clear();
  connections_.clear();
  figures_ = figures;
}

void Canvas::setConnections(const QList<Connection *> &connections)
{
  connections_.clear();
  connections_ = connections;
}

QList<Figure *> Canvas::figures()
{
  return figures_;
}

QList<Connection *> Canvas::connections()
{
  return connections_;
}

void Canvas::setFigureDrawing(bool enable)
{
  isFigureDrawing_ = enable;
}

void Canvas::setFigureMoving(bool enable)
{
  isFigureMoving_ = enable;
  setMouseTracking(enable);
  if (enable)
  {
    setCursor(Qt::OpenHandCursor);
  }
  else
  {
    setCursor(Qt::ArrowCursor);
  }
}

void Canvas::setConnectingFigures(bool enable)
{
  isConnectingFigures_ = enable;
  if (!enable)
  {
    connectionLine_.first.reset();
    connectionLine_.second.reset();
  }
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

    if (currentAction_ != Action::Nothing && !isFigureDrawing_)
    {
      // first part behavior while left mouse button pressed same in actions Move, Connect
      // and Remove: we need determine figure that was edited last, and work with this figure
      auto foundFigure = figureUnderPoint(event->pos());
      if (foundFigure.has_value())
      {
        currentFigure_ = foundFigure.value();
      }
      if (currentFigure_)
      {
        switch (currentAction_)
        {
        case Action::RemoveFigure:
          {
            for (auto it = connections_.begin(); it != connections_.end();)
            {
              if ((*it)->containsFigure(currentFigure_))
              {
                auto deletingConnection = *it;
                it = connections_.erase(it);
                delete deletingConnection;
              }
              else
              {
                ++it;
              }
            }

            figures_.removeAll(currentFigure_);
            delete currentFigure_;
            currentFigure_ = nullptr;
            Logger::log("Canvas remove figure");
          }
          break;
        case Action::MoveFigure:
          {
            setCursor(Qt::ClosedHandCursor);
            Logger::log("Canvas move figure");
          }
          break;
        case Action::ConnectFigures:
          {
            connectionLine_.first = currentFigure_->center();
            connectionLine_.second = event->pos();
            Logger::log("Canvas connect, detected first figure with center <" + QString::number(connectionLine_.first.value().x()) + "> <"
                                                                              + QString::number(connectionLine_.first.value().y()) + ">");
          }
          break;
        default:
          break;
        }
      }
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
  }
  lastPos = event->pos();

  if (isConnectingFigures_)
  {
    connectionLine_.second = event->pos();
    Logger::log("Canvas set second pos for connection line with <" + QString::number(event->pos().x()) + " > <" + QString::number(event->pos().y()) + ">");
  }
  update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
  Logger::log("Canvas mouse release event");

  if (isFigureDrawing_ && currentFigure_)
  {
    figures_.push_back(currentFigure_);
  }
  
  if (isConnectingFigures_)
  {  
    Logger::log("Connecting figure ok");
    auto figureUnderMouse = figureUnderPoint(event->pos());
    decltype(figureUnderMouse) firstFigureInConnection;
    if (connectionLine_.first.has_value())
    {
      firstFigureInConnection = figureUnderPoint(connectionLine_.first.value());
    }
    Logger::log("First figure " + QString::number(firstFigureInConnection.has_value()) + " and second " + QString::number(figureUnderMouse.has_value()));
    if (figureUnderMouse.has_value() && firstFigureInConnection.has_value())
    {
      auto connect = new Connection{firstFigureInConnection.value(), figureUnderMouse.value()};
      connections_.push_back(connect);
    }
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
  for (const auto &item : connections_)
  {
    item->draw(&painter);
  }
  if (currentFigure_)
  {
    currentFigure_->draw(&painter);
  }
  Logger::log("Connection line first " + QString::number(connectionLine_.first.has_value()));
  Logger::log("Connection line second " + QString::number(connectionLine_.second.has_value()));
  if (connectionLine_.first.has_value() && connectionLine_.second.has_value())
  {
    painter.drawLine(connectionLine_.first.value(), connectionLine_.second.value());
  }
}

std::optional<Figure *> Canvas::figureUnderPoint(const QPointF &point) const
{
  // find figure for conection
  std::vector<Figure *> figuresUnderMouse;
  for (const auto &item : figures_)
  {
    if (item->contains(point))
    {
      figuresUnderMouse.push_back(item);
    }
  }
  if (!figuresUnderMouse.empty())
  {
    std::sort(figuresUnderMouse.begin(), figuresUnderMouse.end(), [](Figure * l, Figure *r) {
      return l->lastEdited() < r->lastEdited();
    });

    return figuresUnderMouse[figuresUnderMouse.size() - 1];
  }
  return std::nullopt;
}
