#include "ToolPanel.h"

#include <QKeySequence>

ToolPanel::ToolPanel(QWidget *parent)
  : QToolBar(parent)
  // , rectangleAction_(new QAction{tr("Rectangle")})
  // , triangleAction_(new QAction{tr("Triangle")})
  // , ellipseAction_(new QAction{tr("Ellipse")})

  , connectAction_(new QAction{tr("Connect")})

  , moveAction_(new QAction{tr("Move")})
  , removeAction_(new QAction{tr("Remove")})

  , saveAction_(new QAction{tr("Save")})
  , loadAction_(new QAction{tr("Load")})
{
    rectangleAction_ = addAction(tr("Rectangle"), QKeySequence{tr("Ctrl+R")});
    triangleAction_ = addAction(tr("Triangle"), QKeySequence{tr("Ctrl+T")});
    ellipseAction_ = addAction(tr("Ellipse"), QKeySequence{tr("Ctrl+E")});

    addSeparator();

    addAction(connectAction_);

    addSeparator();

    addAction(moveAction_);
    addAction(removeAction_);

    addSeparator();

    addAction(loadAction_);
    addAction(saveAction_);
}

ToolPanel::~ToolPanel()
{
    delete rectangleAction_;
    delete triangleAction_;
    delete ellipseAction_;

    delete connectAction_;

    delete moveAction_;
    delete removeAction_;

    delete saveAction_;
    delete loadAction_;
};
