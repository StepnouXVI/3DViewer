#include <Views/Components/Composite/Component.h>

#include <QLayout>

Component::Component(QWidget *parent) : QWidget(parent) {}

void Component::fill(QWidget *container, const int &spacing, const int &left,
                     const int &top, const int &right, const int &bottom) {
  setParent(container);
  setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

  container->layout()->addWidget(this);
  container->layout()->setSpacing(spacing);
  container->layout()->setContentsMargins(left, top, right, bottom);
}
