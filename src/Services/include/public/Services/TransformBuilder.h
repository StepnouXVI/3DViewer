#pragma once
#include <DTO/Point3D.h>
#include <DTO/TransformMatrix.h>

namespace services {

class TransformBuilder {
 public:
  static dto::TransformMatrix buildRotateMatrix(dto::Point3D);
  static dto::TransformMatrix buildScaleMatrix(dto::Point3D);
  static dto::TransformMatrix buildMoveMatrix(dto::Point3D);
};

}  // namespace services
