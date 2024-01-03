#pragma once
#include <Models/Light/LightSource.h>

#include <utility>

namespace models {

class DirectedSource : public LightSource {
 public:
  std::pair<dto::Point3D, dto::Point3D> direction;
};

}  // namespace models