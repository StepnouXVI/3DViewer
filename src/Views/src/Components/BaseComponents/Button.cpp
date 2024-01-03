#include <Views/Components/BaseComponents/Button.h>

Button::Button(QWidget *parent) : button_(new QPushButton(this)) {
  setParent(parent);
  setObjectName("custom_button");
  connect(button_, &QPushButton::clicked, this, &Button::clicked);
}

void Button::resizeEvent(QResizeEvent *) { button_->resize(size()); }

void Button::setText(const QString &text) { button_->setText(text); }

QPushButton *Button::getWidget() const { return button_; }

void Button::setObjectName(const QString &objectName) {
  button_->setObjectName(objectName);
}

void Button::setEnabled(bool enabled) { button_->setEnabled(enabled); }
