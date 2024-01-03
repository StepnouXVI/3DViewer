#pragma once

#include <Views/Components/BaseComponents/Button.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/lib/SlidingStackedWidget/slidingstackedwidget.h>

#include <QEasingCurve>

class StackedWidget : public Composite {
  Q_OBJECT

 private:
  SlidingStackedWidget *stackedWidget_;

 public:
  StackedWidget(QWidget *parent = nullptr);

  void addWidget(QWidget *widget) override;
  void setButtons(Button *prev, Button *next);
  void setSpeed(const int &speed);
  void setAnimation(const QEasingCurve::Type &animationType);
  void setObjectName(const QString &objectName);
  int count();
  void removePage(const int &index);
  int currentIndex();
  void setCurrentIndex(const int index);
  void slideToIndex(const int index);
  SlidingStackedWidget *getWidget() const override;
  QWidget *getWidget(const int &index);
  void setEnabled(bool enabled);

 protected:
  void resizeEvent(QResizeEvent *event) override;

 signals:
  void pageChanged(int page);
};
