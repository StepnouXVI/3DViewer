#pragma once

#include <Views/Components/BaseComponents/Label.h>

class Title : public Label {
  Q_OBJECT

 private:
  bool underline_ = false;

 public:
  Title(QWidget *parent = nullptr);
  void setUnderline(const bool &status);
};
