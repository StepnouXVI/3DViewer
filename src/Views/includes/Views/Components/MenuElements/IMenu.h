#pragma once

#include <Controllers/SceneController.h>
#include <Controllers/SceneObjectController.h>
#include <Controllers/TransformableController.h>
#include <Models/SceneObject/SceneObject.h>
#include <Views/Components/BaseComponents/InfoStackedWidget.h>
#include <Views/Components/Builder/Builder.h>
#include <Views/Components/Composite/Composite.h>

#include <memory>

class IMenu : public Composite {
 private:
  QString menuTitle_;

 protected:
  int spacing_ = 15;
  controllers::TransformableControllerPtr currentTransformable;

 public:
  IMenu(QWidget *parent, QString menuTitle)
      : Composite(parent), menuTitle_(menuTitle) {}

 protected:
  void initStackedWidget(InfoStackedWidget *&infoStackedWidget,
                         EntityInfo *entityInfo, Button *&prev, Button *&next) {
    infoStackedWidget = new InfoStackedWidget(entityInfo);
    prev = Builder::getPrevButton();
    next = Builder::getNextButton();
    infoStackedWidget->setButtons(prev, next);
  }

 public:
  QString getMenuTitle() { return menuTitle_; };
};
