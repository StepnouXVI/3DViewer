#pragma once
#include "Models/ISceneDrawer.h"
#include "Models/SceneObject/SceneObject.h"

namespace opengl {

class DrawerOpenGL : models::ISceneDrawer {
 private:
  /* data */
 public:
  DrawerOpenGL();
  void draw(models::TransformableObject&) override;
  ~DrawerOpenGL();
};

}  // namespace opengl