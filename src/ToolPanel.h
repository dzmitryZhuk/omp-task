#pragma once

#include <QToolBar>

class ToolPanel
  : public QToolBar
{
public:
  explicit ToolPanel(QWidget *parent = nullptr);
  virtual ~ToolPanel();
};
