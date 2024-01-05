#pragma once

#include <Views/Components/Composite/Component.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

class Composite : public Component {
 protected:
  int spacing = 15;

 private:
  Qt::Orientation orientation_;
  QLayout *layout_;

 public:
  Composite(const Qt::Orientation &orientation = Qt::Vertical,
            QWidget *parent = nullptr);
  Composite(QWidget *parent);

  void setSpacing(const int &spacing);
  void setMargins(const QMargins &margins);

  void addWidget(QWidget *widget) override;
  bool isComposite() const override;
  QWidget *getWidget() const override;
};
