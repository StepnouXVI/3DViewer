#pragma once

#include <Controllers/IIterableController.h>
#include <Controllers/SceneObjectController.h>
#include <Controllers/TransformableController.h>
#include <DTO/Point3D.h>
#include <DTO/VisualProperty.h>
#include <Models/ISceneDrawer.h>
#include <Models/Scene.h>
#include <Models/SceneObject/SceneObject.h>
#include <Services/SceneCreator.h>
#include <Services/SceneFileOBJReader.h>
#include <Services/TransformBuilder.h>

#include <memory>
#include <string>
#include <vector>

namespace controllers {

enum InteractionMode { Scene, Model, Object };

class SceneController : public TransformableController, IIterableController {
 public:
  explicit SceneController(models::ISceneDrawerPtr& drawer);
  // explicit SceneController(std::unique_ptr<services::SceneCreator>);
  ~SceneController() = default;

  [[nodiscard]] models::ChildrenObjects getChildren() override;
  [[nodiscard]] std::shared_ptr<models::TransformableObject> getCurrentChild()
      override;
  void setActiveChildIdx(int idx) override;
  void draw(models::ISceneDrawerPtr) override;
  [[nodiscard]] std::shared_ptr<models::SceneObject> loadModel(std::string);

 private:
  std::shared_ptr<models::TransformableObject> getTransformableObject()
      override;
  std::unique_ptr<services::SceneCreator> sceneCreator_;
  std::shared_ptr<SceneObjectController> sceneModelController_;
  models::Scene scene_;
};

using SceneControllerPtr = std::shared_ptr<SceneController>;

}  // namespace controllers
