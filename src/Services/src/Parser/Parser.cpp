#include <Services/Parser/Parser.h>

#include <algorithm>
#include <sstream>

namespace Parser {

vertex_t Parser::parseVertex(const std::string& line) {
  vertex_t vertex = {};
  std::istringstream iss(line);
  std::string v;
  iss >> v >> vertex.point.x >> vertex.point.y >> vertex.point.z;
  return vertex_t();
}

#include <sstream>
#include <string>

void readFacet(const std::string& line, Vector<facet_c>& facets,
               Vector<int>& vertices) {
  std::unique_ptr<facet_c> facet = std::make_unique<facet_c>();

  facet->size = std::count(line.begin(), line.end(), ' ') + 1;
  facet->number_of_vertices.resize(facet->size);

  std::istringstream iss(line.substr(2));

  for (int i = 0; i < facet->size; i++) {
    iss >> facet->number_of_vertices[i];

    if (facet->number_of_vertices[i] < 0) {
      facet->number_of_vertices[i] += vertices.size() - 1;
    } else {
      facet->number_of_vertices[i]--;
    }
  }

  facets.push_back(std::move(facet));
}

facet_t Parser::parseFacet(const std::string& line, size_t numberOfVertices) {
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

  return facet_t();
}
}  // namespace Parser