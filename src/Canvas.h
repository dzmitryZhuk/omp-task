#pragma once

#include <QWidget>

class Canvas
  : public QWidget
{
public:
  explicit Canvas(QWidget *parent = nullptr);
  virtual ~Canvas();
};
