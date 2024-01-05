#pragma once

#include <DTO/TransformMatrix.h>
#include <Models/ISceneDrawer.h>

namespace models {

class TransformableObject {
 public:
  void transform(dto::TransformMatrix);
  virtual void draw(ISceneDrawerPtr&);
  dto::TransformMatrix& getModelMatrix();

 protected:
  dto::TransformMatrix modelMatrix_ = dto::TransformMatrix::getIdentityMatrix();
};

}  // namespace models