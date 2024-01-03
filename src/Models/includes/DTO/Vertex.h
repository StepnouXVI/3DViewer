#pragma once
#include <DTO/Point3D.h>

#include <memory>

namespace dto {

struct Vertex {
  Vertex() = default;
  Vertex(dto::Point3D coord) : coord(coord) {}
  //    explicit Vertex(dto::Point3D&& coord): coord(coord){}
  dto::Point3D coord;
  dto::Point3D texture_coord;
  dto::Point3D normal_coord;
};
}  // namespace dto