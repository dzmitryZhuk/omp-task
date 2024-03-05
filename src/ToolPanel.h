#pragma once

#include "config.h"

#include <QToolBar>
#include <QString>
#include <QAction>

class ToolPanel
  : public QToolBar
{
public:
  explicit ToolPanel(QWidget *parent = nullptr);
  virtual ~ToolPanel();

protected:
  QAction *rectangleAction_;
  QAction *triangleAction_;
  QAction *ellipseAction_;

  QAction *connectAction_;

  QAction *moveAction_;
  QAction *removeAction_;

  QAction *saveAction_;
  QAction *openAction_;
};
