#pragma once

#include <QWidget>

class Component : public QWidget {
 public:
  Component(QWidget *parent = nullptr);

  virtual void addWidget(QWidget *widget) = 0;
  virtual bool isComposite() const = 0;
  virtual QWidget *getWidget() const = 0;

  void fill(QWidget *container, const int &spacing = 0, const int &left = 0,
            const int &top = 0, const int &right = 0, const int &bottom = 0);
};
