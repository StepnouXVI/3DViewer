#pragma once

#include <Views/Components/Composite/Composite.h>

#include <QDateTime>
#include <QEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>
#include <QWheelEvent>

class ScrollWidget : public Composite {
  Q_OBJECT

 private:
  QScrollArea *scrollArea_;

 public:
  ScrollWidget(QWidget *parent = nullptr);

  void addWidget(QWidget *widget) override;
  void setObjectName(const QString &objectName);
  QWidget *getWidget() const override;

 protected:
  void resizeEvent(QResizeEvent *event) override;
};
