#pragma once

#include <Views/Components/Composite/Leaf.h>
#include <Views/Components/CustomComponents/CustomCircleSlider.h>

class CircleSlider : public Leaf {
  Q_OBJECT
 private:
  CustomCircleSlider *dial_;

 public:
  CircleSlider(QWidget *parent = nullptr);

  void setValue(double value);
  double getValue();
  CustomCircleSlider *getWidget() const override;
  void setEnabled(bool enabled);

 protected:
  void resizeEvent(QResizeEvent *event) override;

 signals:
  void valueChanged(double value);
};
