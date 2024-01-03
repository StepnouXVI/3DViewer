#pragma once

#include <Views/Components/Composite/Composite.h>
#include <Views/Components/CustomComponents/CustomQOpenGLWidget.h>

#include <QResizeEvent>

class OpenGLWidget : public Composite {
 private:
  CustomQOpenGLWidget *openGLWidget_;

 public:
  OpenGLWidget(QWidget *parent = nullptr);

  CustomQOpenGLWidget *getWidget() const override;

 protected:
  void resizeEvent(QResizeEvent *event) override;
};
