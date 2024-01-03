#pragma once
#include <Services/ISceneFileReader.h>
#include <regex>

namespace services {

namespace consts {
constexpr char VERTEX_REGEX[] = R"(^[vV](\s+[-+]?\d+(([.]\d+)?|([eE][-+]?\d+))){3}(\s)*$)";
constexpr char FACET_REGEX[] = R"(^[f]([ ]([-]?)[0-9]{1,}([/])?(([-]?)[0-9]{1,})?([/])?(([-]?)[0-9]{1,})?){2,}(\s)*$)";
}  // namespace consts

class SceneFileOBJReader : public ISceneFileReader {
 private:
  std::string typename_ = "obj";
  std::string typeDescription_ = "Object Files";

  std::regex vertexRegex_ = std::regex(consts::VERTEX_REGEX);
  std::regex facetRegex_ = std::regex(consts::FACET_REGEX);

  private:

  void getVerticesAndFacetsFromFile(std::ifstream &file, std::vector<vertex_c> &vertices, std::vector<facet_c> &facets);

 public:
  SceneFileData read(const std::string &filename) override;

  std::string getTypename() override;
  std::string getTypeDescription() override;
};

}  // namespace services