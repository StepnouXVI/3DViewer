#include <DTO/Edge.h>
#include <Services/SceneFileOBJReader.h>

#include <vector>

extern "C" {
#include <Services/PureParser/Parser.h>
}

namespace services {
void SceneFileOBJReader::getVerticesAndFacetsFromFile(
    std::ifstream& file, std::vector<vertex_c>& vertices,
    std::vector<facet_c>& facets) {


  std::string line;
  while (std::getline(file, line)) {
    if (std::regex_match(line, vertexRegex_)) {
      vertices.push_back(line);
    } else if (std::regex_match(line, facetRegex_)) {
      facets.push_back(line);
    }
  }

  file.close();
}

SceneFileData SceneFileOBJReader::read(const std::string& filename) {
  SceneFileData sceneFileData;

  std::vector<vertex_c> vertices;
  std::vector<facet_c> facets;

  Vector* vertexes = create_vector(vertex_c);
  Vector* facets = create_vector(facet_c);

  FILE* file = fopen(filename.c_str(), "r");
  readFile(file, vertexes, facets);
  fclose(file);

  for (int i = 0; i < vertexes->size; ++i) {
    auto point = static_cast<vertex_c*>(get_by_index(vertexes, i))->point;
    sceneFileData.v_coord.push_back({point.x, point.y, point.z});
  }

  for (int i = 0; i < facets->size; ++i) {
    dto::Edge edge;

    facet_c* facet = static_cast<facet_c*>(get_by_index(facets, i));
    for (int j = 0; j < facet->size; ++j) {
      edge.v_coord.push_back(facet->number_of_vertecies[j]);
    }

    sceneFileData.faces.push_back(edge);
  }

  clear(vertexes);
  for (int i = 0; i < facets->size; ++i) {
    free((static_cast<facet_c*>(get_by_index(facets, i)))->number_of_vertecies);
  }
  clear(facets);

  return sceneFileData;
}

std::string SceneFileOBJReader::getTypename() { return typename_; }

std::string SceneFileOBJReader::getTypeDescription() {
  return typeDescription_;
}

}  // namespace services