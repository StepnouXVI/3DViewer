#pragma once
#include <vector>

#include "Models/SceneSettings.h"
#include "SceneObject/SceneObject.h"
#include "SceneSettings.h"
#include "TransformableObject.h"

namespace models {

class Scene : public TransformableObject {
 public:
  void addModel(SceneObjectPtr model);
  std::vector<SceneObjectPtr>& getSceneModels();

 private:
  std::vector<SceneObjectPtr> models_;
};

}  // namespace models