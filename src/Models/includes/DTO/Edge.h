#pragma once
#include <DTO/Vertex.h>

#include <vector>

namespace dto {

struct Edge {
  enum EdgeType { HARD, SOFT };
  Edge() = default;
  Edge(std::vector<int> v_coord, EdgeType type)
      : v_coord(v_coord), type(type) {}
  Edge(std::vector<int> v_coord) : v_coord(v_coord) {}

  EdgeType type;

  std::vector<int> v_coord;
};

}  // namespace dto