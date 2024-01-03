#include "Models/TransformableObject.h"

namespace models {

void TransformableObject::transform(dto::TransformMatrix transform) {
  modelMatrix_ = modelMatrix_ * transform;
}

void TransformableObject::draw(ISceneDrawerPtr& drawer) { drawer->draw(*this); }

dto::TransformMatrix& TransformableObject::getModelMatrix() {
  return modelMatrix_;
}

}  // namespace models