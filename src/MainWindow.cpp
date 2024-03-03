#include "MainWindow.h"
#include "Logger.h"

#include <QMessageBox>
#include <QAction>

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
    }
  });

  setFixedSize(900,600);
}

MainWindow::~MainWindow()
{
}
