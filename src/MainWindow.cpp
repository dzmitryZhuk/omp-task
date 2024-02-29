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

  connect(toolPanel_, &ToolPanel::actionTriggered, [this](QAction *action){
    Logger::log("Tool panel action <" + action->text().toStdString() + "> triggered");
  });

  // canvas initialization
  setCentralWidget(canvas_);
}

MainWindow::~MainWindow()
{
}
