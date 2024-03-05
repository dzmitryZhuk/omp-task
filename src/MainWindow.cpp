#include "MainWindow.h"
#include "Logger.h"

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
  }
}

void MainWindow::openTriggered()
{
  // QList<Figure *> figures;
  // QList<Connection *> connections;
  // auto openFilePath = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath(), tr("Images (*.pnt);All (*)"));
  // QFile file(openFilePath);
  // if (file.open(QIODevice::ReadOnly))
  // {
  //   QDataStream in(&file);
  //   qsizetype size;
  //   in >> size;
  //   for (qsizetype i = 0; i < size; i++)
  //   {
  //     Figure readFigure;
  //     auto item = new
  //     insertAction << *item;
  //   }
  // }
}
