#include <Services/Parser/Parser.h>

#include <algorithm>
#include <sstream>

namespace Parser {

vertex_t&& parseVertex(const std::string& line) {
  vertex_t vertex = {};
  std::istringstream iss(line);
  std::string v;
  iss >> v >> vertex.point.x >> vertex.point.y >> vertex.point.z;
  return std::move(vertex);
}

facet_t&& parseFacet(const std::string& line, size_t numberOfVertices) {
  facet_t facet = {};
  std::istringstream iss(line.substr(2));

  facet.size = std::count(line.begin(), line.end(), ' ') + 1;
  facet.numbersOfVertices.resize(facet.size);

  for (int i = 0; i < facet.size; i++) {
    iss >> facet.numbersOfVertices[i];

    if (facet.numbersOfVertices[i] < 0) {
      facet.numbersOfVertices[i] += numberOfVertices - 1;
    } else {
      facet.numbersOfVertices[i]--;
    }
  }

  return std::move(facet);
}
}  // namespace Parser