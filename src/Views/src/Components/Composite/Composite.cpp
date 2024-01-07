#include <Views/Components/Composite/Composite.h>

#include <QWidget>

Composite::Composite(const Qt::Orientation &orientation, QWidget *parent)
    : Component(parent), orientation_(orientation) {
  setParent(parent);

  if (orientation == Qt::Vertical) {
    layout_ = new QVBoxLayout(this);
  } else {
    layout_ = new QHBoxLayout(this);
  }
  layout_->setSpacing(0);
  layout_->setContentsMargins(0, 0, 0, 0);

  this->setLayout(layout_);
}

Composite::Composite(QWidget *parent) : Composite(Qt::Vertical, parent) {}

void Composite::setSpacing(const int &spacing) { layout_->setSpacing(spacing); }

void Composite::setMargins(const QMargins &margins) {
  layout_->setContentsMargins(margins);
}

void Composite::addWidget(QWidget *widget) {
  widget->setParent(this);
  layout_->addWidget(widget);
}

bool Composite::isComposite() const { return true; }
QWidget *Composite::getWidget() const { return nullptr;}
