#pragma once
#include <Services/SceneFileData.h>

#include <fstream>

namespace services {

class ISceneFileReader {
 public:
  virtual SceneFileData read(const std::string &filename) = 0;
  virtual std::string getTypename() = 0;
  virtual std::string getTypeDescription() = 0;
  virtual ~ISceneFileReader() {}
};

}  // namespace services