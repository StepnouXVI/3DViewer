#pragma once
#include <DTO/Edge.h>
#include <DTO/Point3D.h>

#include <vector>

namespace services {

/**
 * @todo Union v_coord, vn_coord, vt_coord, vp_coord in Vertex(create in parsing
 * time)
 */
class SceneFileData {
 public:
  std::vector<dto::Point3D> v_coord;
  std::vector<dto::Point3D> vn_coord;
  std::vector<dto::Point3D> vt_coord;
  std::vector<dto::Point3D> vp_coord;
  std::vector<dto::Edge> faces;
  std::pair<int, int> group;
  std::pair<int, int> objects;
  bool isEmpty() const;
};

}  // namespace services