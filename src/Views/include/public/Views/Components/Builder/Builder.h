#pragma once

#include <Views/Components/BaseComponents/Button.h>
#include <Views/Components/BaseComponents/CircleSlider.h>
#include <Views/Components/BaseComponents/Label.h>
#include <Views/Components/BaseComponents/OpenGLWidget.h>
#include <Views/Components/BaseComponents/ScrollWidget.h>
#include <Views/Components/BaseComponents/StackedWidget.h>
#include <Views/Components/BaseComponents/SwitchMenu.h>
#include <Views/Components/BaseComponents/TextBox.h>
#include <Views/Components/BaseComponents/Title.h>
#include <Views/Components/Builder/ConnectionData.h>
#include <Views/Components/Composite/Leaf.h>

#include <QEasingCurve>
#include <QFontDatabase>
#include <functional>

class Builder {
 public:
  static int fixedHeight_;
  static void applyStyle(Component *widget);
  static void setFixedHeight(int fixedHeight);
  static Button *getButton(const QString &text);
  static Button *getPrevButton();
  static Button *getNextButton();
  static CircleSlider *getCircleSlider();
  static TextBox *getTextBox(const QString &text);
  static Label *getLabel(const QString &text,
                         const Qt::Alignment &alignment = Qt::AlignLeft);
  static Title *getTitle(const QString &text, const bool &underline);
  static SwitchMenu *getSwitchMenu(const QVector<QString> &items);
  static StackedWidget *getStackedWidget(const QVector<Component *> &items,
                                         Button *prev, Button *next);
  static ScrollWidget *getScrollWidget(Component *widget);
  static OpenGLWidget *getOpenGLWidget(Component *parent = nullptr);
};
