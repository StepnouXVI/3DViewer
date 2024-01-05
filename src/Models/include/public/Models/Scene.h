#pragma once
#include <vector>

#include <Models/SceneObject/SceneObject.h>
#include <Models/SceneSettings.h>
#include <Models/TransformableObject.h>

namespace models {

class Scene : public TransformableObject {
 public:
  void addModel(SceneObjectPtr model);
  std::vector<SceneObjectPtr>& getSceneModels();

 private:
  std::vector<SceneObjectPtr> models_;
};

}  // namespace models