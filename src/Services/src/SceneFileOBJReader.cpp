#include <DTO/Edge.h>

#include <Services/SceneFileOBJReader.h>
#include <Services/Parser/Parser.h>

#include <vector>

namespace services {
void SceneFileOBJReader::getVerticesAndFacetsFromFile(
    std::ifstream& file, std::vector<Parser::vertex_t>& vertices,
    std::vector<Parser::facet_t>& facets) {
  std::string line;
  while (std::getline(file, line)) {
    if (std::regex_match(line, vertexRegex_)) {
      vertices.push_back(std::move(Parser::parseVertex(line)));
    } else if (std::regex_match(line, facetRegex_)) {
      facets.push_back(std::move(Parser::parseFacet(line, vertices.size())));
    }
  }
}

std::vector<dto::Point3D> SceneFileOBJReader::convertToDtoPoints(
    std::vector<Parser::vertex_t>& vertices) {
  std::vector<dto::Point3D> points;
  for (auto& vertex : vertices) {
    points.push_back({vertex.point.x, vertex.point.y, vertex.point.z});
  }
  return points;
}

std::vector<dto::Edge> SceneFileOBJReader::convertToDtoEdges(
    std::vector<Parser::facet_t>& facets) {
  std::vector<dto::Edge> edges;
  for (auto& facet : facets) {
    dto::Edge edge;
    for (auto& number : facet.numbersOfVertices) {
      edge.v_coord.push_back(number);
    }
    edges.push_back(std::move(edge));
  }
  return edges;
}

SceneFileData SceneFileOBJReader::read(const std::string& filename) {
  SceneFileData sceneFileData;

  std::vector<Parser::vertex_t> vertices;
  std::vector<Parser::facet_t> facets;

  auto file = std::ifstream(filename);
  if (!file.is_open()) {
    throw std::runtime_error("File not found: " + filename);
  }

  getVerticesAndFacetsFromFile(file, vertices, facets);

  file.close();

  sceneFileData.v_coord = std::move(convertToDtoPoints(vertices));
  sceneFileData.faces = std::move(convertToDtoEdges(facets));

  return sceneFileData;
}

std::string SceneFileOBJReader::getTypename() { return typename_; }

std::string SceneFileOBJReader::getTypeDescription() {
  return typeDescription_;
}

}  // namespace services
