#pragma once

#include <Controllers/IIterableController.h>
#include <Controllers/TransformableController.h>
#include <DTO/Point3D.h>
#include <DTO/VisualProperty.h>
#include <Models/ISceneDrawer.h>
#include <Models/Scene.h>
#include <Models/SceneObject/SceneObject.h>
#include <Services/TransformBuilder.h>

#include <memory>
#include <string>
#include <vector>

namespace controllers {
class SceneObjectController;

using SceneObjectControllerPtr = std::shared_ptr<SceneObjectController>;

class SceneObjectController final : public TransformableController,
                                    IIterableController {
 public:
  SceneObjectController(models::ISceneDrawerPtr& drawer)
      : TransformableController(drawer){};
  ~SceneObjectController() = default;

  void setActiveChildIdx(int idx) override;
  void draw(models::ISceneDrawerPtr drawer) override;

  void injectChild(SceneObjectControllerPtr);
  void injectModel(models::SceneObjectPtr);
  void setVisualProperty(dto::VisualProperty&&);
  void removeTexture();

  std::shared_ptr<models::SceneObject> getSceneObject();

  std::shared_ptr<models::TransformableObject> getCurrentChild() override;
  models::ChildrenObjects getChildren() override;

 private:
  std::shared_ptr<models::TransformableObject> getTransformableObject()
      override;
  std::shared_ptr<SceneObjectController> childController_;
  int currentChildIndex_;
  std::shared_ptr<models::SceneObject> sceneObject_;
};

}  // namespace controllers
