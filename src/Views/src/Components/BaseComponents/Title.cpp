#include <Views/Components/BaseComponents/Title.h>

Title::Title(QWidget *parent) : Label(parent) { setObjectName("title"); }

void Title::setUnderline(const bool &status) {
  underline_ = status;
  getWidget()->setProperty("underline", status);
}
