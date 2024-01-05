#pragma once
#include <Models/SceneObject/SceneObject.h>
#include <Services/ISceneFileReader.h>
#include <Services/SceneObjectFactory.h>

#include <fstream>
#include <memory>

namespace services {

class SceneCreator {
 public:
  SceneCreator();
  SceneCreator(std::unique_ptr<ISceneFileReader> reader,
               std::unique_ptr<SceneObjectFactory> factory);
  std::shared_ptr<models::SceneObject> createObject(std::string&& filename);

 private:
  std::unique_ptr<ISceneFileReader> reader;
  std::unique_ptr<SceneObjectFactory> factory;
};

}  // namespace services
