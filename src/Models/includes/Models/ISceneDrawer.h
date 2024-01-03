#pragma once
#include <memory>

namespace models {

class TransformableObject;

class ISceneDrawer {
 public:
  virtual void draw(TransformableObject&) = 0;
};

using ISceneDrawerPtr = std::shared_ptr<ISceneDrawer>;

}  // namespace models
