#pragma once
#include <Models/SceneObject/SceneObject.h>

#include <Controllers/TransformableController.h>

namespace controllers {

class IIterableController {
 public:
  /**
   * @brief Set the active child index
   * @todo Internal TransformableController Iterator
   */
  virtual void setActiveChildIdx(int) = 0;
  virtual std::shared_ptr<models::TransformableObject> getCurrentChild() = 0;
  virtual models::ChildrenObjects getChildren() = 0;
};

}  // namespace controllers
