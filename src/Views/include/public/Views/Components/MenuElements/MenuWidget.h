#pragma once

#include <Views/Components/Builder/Builder.h>
#include <Views/Components/Composite/Component.h>
#include <Views/Components/MenuElements/MenuItems/ControlMenu.h>
#include <Views/Components/MenuElements/MenuItems/CreationMenu.h>
#include <Views/Components/MenuElements/MenuItems/ObjectMenu.h>
#include <Views/Components/MenuElements/MenuItems/SaveMenu.h>
#include <Views/Components/MenuElements/MenuItems/SceneMenu.h>

#include <iostream>
#include <unordered_map>

class MenuWidget : public QObject {
  Q_OBJECT
 public:
  MenuWidget(controllers::SceneControllerPtr scene,
             controllers::SceneObjectControllerPtr model,
             controllers::SceneObjectControllerPtr object)
      : scene_(scene), model_(model), object_(object) {
    composeUI();
  }

 private:
  Button *prevMenuElement;
  Button *nextMenuElement;

  QVector<Component *> menuElements;
  QVector<Component *> menuTitles;

  Composite *header_;
  Composite *menu_;
  Composite *controlMenu_;
  OpenGLWidget *openGLWidget_;

  controllers::SceneControllerPtr scene_;
  controllers::SceneObjectControllerPtr model_;
  controllers::SceneObjectControllerPtr object_;

  void composeUI() {
    openGLWidget_ = Builder::getOpenGLWidget();
    controlMenu_ = new ControlMenu(scene_, model_, object_, openGLWidget_);

    CreationMenu *creationMenu = new CreationMenu(scene_, model_);
    SceneMenu *sceneMenu = new SceneMenu(openGLWidget_);
    ObjectMenu *objectMenu = new ObjectMenu(model_, object_);
    SaveMenu *saveMenu = new SaveMenu(openGLWidget_);

    std::vector<IMenu *> items = {creationMenu, sceneMenu, objectMenu,
                                  saveMenu};

    prevMenuElement = Builder::getPrevButton();
    nextMenuElement = Builder::getNextButton();

    prevMenuElement->setObjectName("header_button");
    nextMenuElement->setObjectName("header_button");

    for (const auto &it : items) {
      menuTitles.append(Builder::getTitle(it->getMenuTitle(), false));
      menuElements.append(Builder::getScrollWidget(it));
    }

    StackedWidget *menuStackedWidget = Builder::getStackedWidget(
        menuElements, prevMenuElement, nextMenuElement);
    StackedWidget *headerStackedWidget =
        Builder::getStackedWidget(menuTitles, prevMenuElement, nextMenuElement);

    header_ = ConcreteCompositor::getRow(
        {prevMenuElement, headerStackedWidget, nextMenuElement});
    menu_ = menuStackedWidget;
  }

 public:
  Composite *getHeader() { return header_; }

  Composite *getMenu() { return menu_; }

  Composite *getControlMenu() { return controlMenu_; }

  OpenGLWidget *getOpenGLWidget() { return openGLWidget_; }
};
