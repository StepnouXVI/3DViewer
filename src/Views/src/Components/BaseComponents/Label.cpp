#include <Views/Components/BaseComponents/Label.h>

Label::Label(QWidget *parent) : label_(new QLabel(this)) {
  setParent(parent);
  setObjectName("label");
}

void Label::setAlignment(Qt::Alignment alignment) {
  label_->setAlignment(alignment);
}

void Label::resizeEvent(QResizeEvent *event) { label_->resize(size()); }

void Label::setText(const QString &text) { label_->setText(text); }

QLabel *Label::getWidget() const { return label_; }

void Label::setObjectName(const QString &objectName) {
  label_->setObjectName(objectName);
}

void Label::setEnabled(bool enabled) { label_->setEnabled(enabled); }
