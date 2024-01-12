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
             controllers::SceneObjectControllerPtr object);

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

  void composeUI();

 public:
  Composite *getHeader();

  Composite *getMenu();

  Composite *getControlMenu();

  OpenGLWidget *getOpenGLWidget();
};
