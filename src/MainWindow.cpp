#include "MainWindow.h"
#include "Logger.h"
#include "Figures/Rectangle.h"
#include "Figures/Triangle.h"
#include "Figures/Ellipse.h"

#include <QMessageBox>
#include <QAction>
#include <QFileDialog>
#include <QDir>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , toolPanel_(new ToolPanel{this})
  , canvas_(new Canvas{this})
{
  // tool panel initialization
  addToolBar(Qt::TopToolBarArea, toolPanel_);
  toolPanel_->setMovable(false);

  // canvas initialization
  setCentralWidget(canvas_);

  connect(toolPanel_, &ToolPanel::actionTriggered, [this](QAction *action){
    Logger::log("Tool panel action <" + action->text().toStdString() + "> triggered");
    if (action->text().compare(tr("Rectangle")) == 0)
    {
      this->canvas_->setRectangleDrawingAction();
    } else
    if (action->text().compare(tr("Triangle")) == 0)
    {
      this->canvas_->setTriangleDrawingAction();
    } else
    if (action->text().compare(tr("Ellipse")) == 0)
    {
      this->canvas_->setEllipseDrawingAction();
    } else
    if (action->text().compare(tr("Move")) == 0)
    {
      this->canvas_->setMovingFigureAction();
    } else
    if (action->text().compare(tr("Remove")) == 0)
    {
      this->canvas_->setRemovingFigureAction();
    } else
    if (action->text().compare(tr("Connect")) == 0)
    {
      this->canvas_->setConnectingFiguresAction();
    } else
    if (action->text().compare(tr("Save")) == 0)
    {
      this->saveTriggered();
    } else
    if (action->text().compare(tr("Open")) == 0)
    {
      this->openTriggered();
    }
  });

  setFixedSize(900,600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::saveTriggered()
{
  auto figures = canvas_->figures();
  auto connections = canvas_->connections();
  auto saveFilePath = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::currentPath(), tr("Images (*.pnt)"));
  QFile file(saveFilePath);
  if (file.open(QIODevice::WriteOnly))
  {
    QDataStream out(&file);
    out << figures.size();
    for (const auto *item : figures)
    {
      out << item;
    }
    // save connections
  }
}

void MainWindow::openTriggered()
{
  QList<Figure *> figures;
  QList<Connection *> connections;
  auto openFilePath = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath(), tr("Images (*.pnt);All (*)"));
  QFile file(openFilePath);
  if (file.open(QIODevice::ReadOnly))
  {
    QDataStream in(&file);
    decltype(figures.size()) size;
    in >> size;
    for (decltype(figures.size()) i = 0; i < size; i++)
    {
      QString className;
      QRectF boundingRect;
      quint64 lastEdited;
      in >> className;
      in >> boundingRect;
      in >> lastEdited;
      Figure *figure;
      if (className.compare("Rectangle") == 0)
      {
        figure = new Rectangle{boundingRect, canvas_};
      } else
      if (className.compare("Triangle") == 0)
      {
        figure = new Triangle{boundingRect, canvas_};
      } else
      if (className.compare("Ellipse") == 0)
      {
        figure = new Ellipse{boundingRect, canvas_};
      }
      figure->setLastEdited(lastEdited);
      figures.push_back(figure);
    }
    canvas_->setFigures(figures);
    // load connections
  }
}
