#pragma once

#include <Views/Components/Composite/Leaf.h>

#include <QLabel>
#include <QResizeEvent>

class Label : public Leaf {
 private:
  QLabel *label_;

 public:
  Label(QWidget *parent = nullptr);

  void setText(const QString &text);
  void setAlignment(Qt::Alignment alignment);
  void setObjectName(const QString &objectName);
  void setEnabled(bool enabled);

  QLabel *getWidget() const override;

 protected:
  void resizeEvent(QResizeEvent *event) override;
};
