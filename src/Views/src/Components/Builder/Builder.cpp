#include <Views/Components/Builder/Builder.h>

int Builder::fixedHeight_ = 45;

void Builder::setFixedHeight(int fixedHeight) { fixedHeight_ = fixedHeight; }

Button* Builder::getButton(const QString& text) {
  Button* component = new Button();
  component->setText(text);
  component->setFixedHeight(fixedHeight_ * 0.95);

  return component;
}

Button* Builder::getPrevButton() { return getButton("<"); }

Button* Builder::getNextButton() { return getButton(">"); }

CircleSlider* Builder::getCircleSlider() { return new CircleSlider(); }

TextBox* Builder::getTextBox(const QString& text) {
  TextBox* component = new TextBox();
  component->setText(text);
  component->setFixedHeight(fixedHeight_ * 0.95);
  component->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  return component;
}

Label* Builder::getLabel(const QString& text, const Qt::Alignment& alignment) {
  Label* component = new Label();
  component->setText(text);
  component->setFixedHeight(fixedHeight_);
  component->setAlignment(Qt::AlignVCenter | alignment);
  return component;
}

Title* Builder::getTitle(const QString& text, const bool& underline) {
  Title* component = new Title();
  component->setText(text);
  component->setFixedHeight(fixedHeight_ * 1.5);
  component->setUnderline(underline);
  component->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  return component;
}

SwitchMenu* Builder::getSwitchMenu(const QVector<QString>& items) {
  SwitchMenu* component = new SwitchMenu();
  component->addItems(items);
  component->setFixedHeight(fixedHeight_);

  return component;
}

StackedWidget* Builder::getStackedWidget(const QVector<Component*>& items,
                                         Button* prev, Button* next) {
  StackedWidget* component = new StackedWidget();

  int maxHeight = items[0]->height();
  for (const auto& it : items) {
    component->addWidget(it);
    if (it->height() > maxHeight) maxHeight = it->height();
  }
  component->setButtons(prev, next);

  return component;
}

ScrollWidget* Builder::getScrollWidget(Component* widget) {
  ScrollWidget* component = new ScrollWidget();

  component->addWidget(widget);

  return component;
}

OpenGLWidget* Builder::getOpenGLWidget(Component* parent) {
  OpenGLWidget* component = new OpenGLWidget(parent);

  return component;
}