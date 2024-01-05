#pragma once

namespace dto {

struct Point3D {
  Point3D() : x(0.0), y(0.0), z(0.0){};
  Point3D(double x, double y, double z) : x(x), y(y), z(z){};
  double x, y, z;
};

}  // namespace dto