#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , toolPanel_(new ToolPanel{this})
  , canvas_(new Canvas{this})
{
    addToolBar(Qt::TopToolBarArea, toolPanel_);
}

MainWindow::~MainWindow()
{
}
