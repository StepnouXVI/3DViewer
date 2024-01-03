#include <Views/Components/BaseComponents/TextBox.h>

TextBox::TextBox(QWidget *parent) : lineEdit_(new QLineEdit(this)) {
  setParent(parent);
  lineEdit_->setObjectName("textbox");
}

void TextBox::resizeEvent(QResizeEvent *event) { lineEdit_->resize(size()); }

void TextBox::setText(const QString &text) { lineEdit_->setText(text); }

QLineEdit *TextBox::getWidget() const { return lineEdit_; }

void TextBox::setAlignment(const Qt::Alignment &alignment) {
  lineEdit_->setAlignment(alignment);
}

void TextBox::setEnabled(bool enabled) { lineEdit_->setEnabled(enabled); }
