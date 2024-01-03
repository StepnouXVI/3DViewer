#pragma once

#include <Services/OpenGL/ShaderDrawer.h>
#include <Views/Components/Composite/Composite.h>
#include <Views/Components/MenuElements/MenuWidget.h>

class MocShaderDrawer : public models::ISceneDrawer {
 public:
  void draw(models::TransformableObject&) override {}
};

class ViewerMainWindow : public Composite {
 private:
  static const int spacing_ = 15;

  models::ISceneDrawerPtr drawer_;

  controllers::SceneControllerPtr scene_;
  controllers::SceneObjectControllerPtr model_;
  controllers::SceneObjectControllerPtr object_;

 public:
  ViewerMainWindow();
};
