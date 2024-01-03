#include <Views/Components/BaseComponents/ScrollWidget.h>

ScrollWidget::ScrollWidget(QWidget *parent)
    : scrollArea_(new QScrollArea(this)) {
  setParent(parent);
  scrollArea_->setWidgetResizable(true);
  scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setObjectName("scroll_widget");
}

void ScrollWidget::resizeEvent(QResizeEvent *event) {
  scrollArea_->resize(size());
}

void ScrollWidget::setObjectName(const QString &objectName) {
  scrollArea_->setObjectName(objectName);
}

void ScrollWidget::addWidget(QWidget *widget) {
  scrollArea_->setWidget(widget);
  widget->setObjectName("scroll_widget_item");
}

QWidget *ScrollWidget::getWidget() const { return scrollArea_; }
