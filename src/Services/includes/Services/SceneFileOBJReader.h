#pragma once
#include <Services/ISceneFileReader.h>

namespace services {

class SceneFileOBJReader : public ISceneFileReader {
 private:
  std::string typename_ = "obj";
  std::string typeDescription_ = "Object Files";

 public:
  SceneFileData read(const std::string &filename) override;

  std::string getTypename() override;
  std::string getTypeDescription() override;
};

}  // namespace services