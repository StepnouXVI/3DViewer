#include <Views/Components/BaseComponents/CircleSlider.h>

CircleSlider::CircleSlider(QWidget *parent)
    : dial_(new CustomCircleSlider(this)) {
  setParent(parent);
  dial_->setObjectName("custom_circle_slider");
  connect(dial_, &CustomCircleSlider::valueChanged, this,
          [this]() { emit valueChanged(dial_->getValue()); });
}

void CircleSlider::setValue(double value) { dial_->setValue(value); }

double CircleSlider::getValue() { return dial_->getValue(); }

void CircleSlider::resizeEvent(QResizeEvent *) {
  dial_->resize(width(), width());
}

CustomCircleSlider *CircleSlider::getWidget() const { return dial_; }
