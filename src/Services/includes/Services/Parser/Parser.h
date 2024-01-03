#pragma once

#include <string>
#include <vector>

namespace Parser {

typedef struct point_3d {
  double x, y, z;
} point_3d_t;

typedef union vertex {
  double points[3];
  point_3d_t point;
} vertex_t;

typedef struct facet {
  std::vector<int> numbersOfVertices;
  int size;
} facet_t;

class Parser {
 public:
  static vertex_t parseVertex(const std::string& line);
  static facet_t parseFacet(const std::string& line, size_t numberOfVertices);
};
}  // namespace Parser