#pragma once

#include <Views/Components/Composite/Leaf.h>

#include <QLineEdit>

class TextBox : public Leaf {
 private:
  QLineEdit *lineEdit_;

 public:
  TextBox(QWidget *parent = nullptr);

  void setText(const QString &text);
  void setAlignment(const Qt::Alignment &alignment);
  QLineEdit *getWidget() const override;
  void setEnabled(bool enabled);

 protected:
  void resizeEvent(QResizeEvent *event) override;
};
