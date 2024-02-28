#include "MainWindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , toolPanel_(new ToolPanel{this})
  , canvas_(new Canvas{this})
{
  addToolBar(Qt::TopToolBarArea, toolPanel_);
  toolPanel_->setMovable(false);
}

MainWindow::~MainWindow()
{
}
