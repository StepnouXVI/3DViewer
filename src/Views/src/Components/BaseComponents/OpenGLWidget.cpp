#include <Views/Components/BaseComponents/OpenGLWidget.h>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : openGLWidget_(new CustomQOpenGLWidget(this)) {
  setParent(parent);
}

CustomQOpenGLWidget *OpenGLWidget::getWidget() const { return openGLWidget_; }

void OpenGLWidget::resizeEvent(QResizeEvent *) {
  openGLWidget_->resize(width(), height());
}
