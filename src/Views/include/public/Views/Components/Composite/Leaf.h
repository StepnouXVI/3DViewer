#pragma once

#include <Views/Components/Composite/Composite.h>

#include <QWidget>

class Leaf : public Component {
 public:
  Leaf(QWidget *parent = nullptr);

  bool isComposite() const override;
  void addWidget(QWidget *) override;
};
