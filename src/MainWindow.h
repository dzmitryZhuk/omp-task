#pragma once

#include "Canvas.h"
#include "ToolPanel.h"
#include "config.h"

#include <QMainWindow>

class MainWindow
  : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  virtual ~MainWindow();
protected:
  Canvas *canvas_;
  ToolPanel *toolPanel_;
};
