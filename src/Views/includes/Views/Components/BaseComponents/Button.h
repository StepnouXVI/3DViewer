#pragma once

#include <Views/Components/Composite/Leaf.h>

#include <QPushButton>
#include <QResizeEvent>

class Button : public Leaf {
  Q_OBJECT

 private:
  QPushButton *button_;

 public:
  Button(QWidget *parent = nullptr);
  void setText(const QString &text);
  QPushButton *getWidget() const override;
  void setObjectName(const QString &objectName);
  void setEnabled(bool enabled);

 protected:
  void resizeEvent(QResizeEvent *) override;

 signals:
  void clicked();
};