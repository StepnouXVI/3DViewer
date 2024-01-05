#pragma once

#include <Controllers/TransformableController.h>
#include <Views/Components/Builder/Builder.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/Components/Composite/ConcreteCompositor.h>
#include <Views/Components/MenuElements/IMenu.h>

#include <QStyle>
#include <QStyleOption>
#include <functional>
#include <iostream>
#include <unordered_map>

class ControlMenu : public IMenu {
  Q_OBJECT

 private:
  struct UiComponents {
    SwitchMenu *entitySwitchMenu =
        Builder::getSwitchMenu({"scene", "model", "object"});
    SwitchMenu *transformSwitchMenu =
        Builder::getSwitchMenu({"move", "rotate", "scale"});
    SwitchMenu *axisSwitchMenu = Builder::getSwitchMenu({"x", "y", "z"});
    CircleSlider *circleSlider = Builder::getCircleSlider();
  };

  UiComponents ui;

  enum Entity { SCENE, MODEL, OBJECT };
  enum Axis { X, Y, Z };
  enum Transform { MOVE, ROTATE, SCALE };

  int activeEntity_ = Entity::SCENE;
  int activeTransform_ = Transform::MOVE;
  int activeAxis_ = Axis::X;

  double state_[3][3][3] = {{{0.0}}};
  std::unordered_map<int, std::function<void(dto::Point3D)>>
      transformFunctions_;
  std::unordered_map<int, controllers::TransformableControllerPtr>
      transformControllers_;

  OpenGLWidget *openGLWidget_;

 public:
  ControlMenu(controllers::SceneControllerPtr scene,
              controllers::SceneObjectControllerPtr model,
              controllers::SceneObjectControllerPtr object,
              OpenGLWidget *openGLWidget, QWidget *parent = nullptr)
      : IMenu(parent, "Control"), openGLWidget_(openGLWidget) {
    transformControllers_.insert(std::make_pair(Entity::SCENE, scene));
    transformControllers_.insert(std::make_pair(Entity::MODEL, model));
    transformControllers_.insert(std::make_pair(Entity::OBJECT, object));

    initUI();
    setupConnections();
    composeUI();
  }

 protected:
  void paintEvent(QPaintEvent *pe) {
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
  }

 private:
  void initUI() {
    currentTransformable = transformControllers_[Entity::MODEL];
    ui.entitySwitchMenu->setEnabled(false);

    transformFunctions_.insert(
        std::make_pair(Transform::MOVE, [this](dto::Point3D point) {
          currentTransformable->moveObject(std::move(point));
        }));
    transformFunctions_.insert(
        std::make_pair(Transform::ROTATE, [this](dto::Point3D point) {
          currentTransformable->rotateObject(std::move(point));
        }));
    transformFunctions_.insert(
        std::make_pair(Transform::SCALE, [this](dto::Point3D point) {
          currentTransformable->scaleObject(std::move(point));
        }));
  }

  void setupConnections() {
    connect(ui.entitySwitchMenu, &SwitchMenu::activeItemChanged, this,
            &ControlMenu::entityChanged);
    connect(ui.axisSwitchMenu, &SwitchMenu::activeItemChanged, this,
            &ControlMenu::axisChanged);
    connect(ui.transformSwitchMenu, &SwitchMenu::activeItemChanged, this,
            &ControlMenu::transformChanged);
    connect(ui.circleSlider, &CircleSlider::valueChanged, this,
            &ControlMenu::valueChanged);
    connect(ModelInfo::getModelInfo().get(), &ModelInfo::dataAdded, this,
            &ControlMenu::modelAdded);
  }

  void modelAdded() {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
          state_[i][j][k] = 0;
        }
      }
    }
    ui.entitySwitchMenu->setEnabledItems({Entity::MODEL});
    double *state = state_[activeEntity_][activeTransform_];
  }

  void valueChanged(double value) {
    if (!dynamic_cast<controllers::SceneController *>(
             transformControllers_[Entity::SCENE].get())
             ->getChildren()
             .empty()) {
      double *state = state_[activeEntity_][activeTransform_];
      state[activeAxis_] = value;
      transformFunctions_[activeTransform_](
          dto::Point3D(state[Axis::X], state[Axis::Y], state[Axis::Z]));
    }
  }

  void composeUI() {
    auto rowLayout = ConcreteCompositor::getRow({
        ConcreteCompositor::getBlock(
            {ui.entitySwitchMenu, ui.transformSwitchMenu, ui.axisSwitchMenu}),
        ConcreteCompositor::getBlock({ui.circleSlider}, 0, spacing_, 0,
                                     spacing_, 0),
    });
    rowLayout->fill(this, spacing_, spacing_, spacing_, spacing_, spacing_);
  }

  void loadState() {
    ui.circleSlider->setValue(
        state_[activeEntity_][activeTransform_][activeAxis_]);
  }

 private slots:
  void entityChanged(int entity) {
    currentTransformable = transformControllers_[activeEntity_ = entity];
    loadState();
  }

  void axisChanged(int transform) {
    activeTransform_ = transform;
    loadState();
  }

  void transformChanged(int axis) {
    activeAxis_ = axis;
    loadState();
  }
};