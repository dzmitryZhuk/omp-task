#pragma once

#include "Canvas.h"
#include "ToolPanel.h"

class MainWindow
{
public:
  MainWindow(/* args */);
  ~MainWindow();
protected:
  Canvas canvas_;
  ToolPanel toolPanel_;
};
