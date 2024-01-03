#include <Views/Components/BaseComponents/StackedWidget.h>

StackedWidget::StackedWidget(QWidget *parent)
    : stackedWidget_(new SlidingStackedWidget(this)) {
  setParent(parent);
  setObjectName("stacked_widget");

  stackedWidget_->setWrap(true);
  setAnimation(QEasingCurve::Type::OutQuart);
  setSpeed(400);

  connect(stackedWidget_, &QStackedWidget::currentChanged,
          [this](int index) { emit pageChanged(index); });
}

void StackedWidget::resizeEvent(QResizeEvent *) {
  stackedWidget_->resize(size());
}

void StackedWidget::addWidget(QWidget *widget) {
  stackedWidget_->addWidget(widget);
  widget->setObjectName("stacked_widget_item");
}

SlidingStackedWidget *StackedWidget::getWidget() const {
  return stackedWidget_;
}

void StackedWidget::setButtons(Button *prev, Button *next) {
  connect(prev->getWidget(), &QAbstractButton::clicked,
          [this] { stackedWidget_->slideInPrev(); });

  connect(next->getWidget(), &QAbstractButton::clicked,
          [this] { stackedWidget_->slideInNext(); });

  prev->setObjectName("stacked_widget_button");
  next->setObjectName("stacked_widget_button");
}

void StackedWidget::setSpeed(const int &speed) {
  stackedWidget_->setSpeed(speed);
}

void StackedWidget::setObjectName(const QString &objectName) {
  stackedWidget_->setObjectName(objectName);
}

void StackedWidget::slideToIndex(int index) {
  stackedWidget_->slideInIdx(index, SlidingStackedWidget::RIGHT2LEFT);
}

void StackedWidget::setCurrentIndex(int index) {
  stackedWidget_->setCurrentIndex(index);
}

void StackedWidget::setAnimation(const QEasingCurve::Type &animationType) {
  stackedWidget_->setAnimation(animationType);
}

int StackedWidget::count() { return stackedWidget_->count(); }

QWidget *StackedWidget::getWidget(const int &index) {
  return stackedWidget_->widget(index);
}

void StackedWidget::removePage(const int &index) {
  QWidget *page = getWidget(index);
  stackedWidget_->removeWidget(page);
  delete page;
}

int StackedWidget::currentIndex() { return stackedWidget_->currentIndex(); }

void StackedWidget::setEnabled(bool enabled) {
  stackedWidget_->setEnabled(enabled);
}
