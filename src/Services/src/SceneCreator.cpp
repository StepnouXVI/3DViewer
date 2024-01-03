#include <Services/OpenGL/SceneObjectOpenGLFactory.h>
#include <Services/SceneCreator.h>
#include <Services/SceneFileOBJReader.h>

#include <exception>
#include <fstream>
#include <memory>

namespace services {

/**
 * @brief Temporary constructor for DI
 * @todo Remove it
 */
SceneCreator::SceneCreator() {
  //    reader = std::unique_ptr<ISceneFileReader>(new SceneFileOBJReader());
  reader = std::make_unique<SceneFileOBJReader>();
  //    factory = std::unique_ptr<SceneObjectFactory>(new
  //    opengl::SceneObjectOpenGLFactory());
  factory = std::make_unique<opengl::SceneObjectOpenGLFactory>();
}

/**
 * @brief Constructor for DI
 * @warning This constructor is not implemented yet (3DViewer 1.0).
 * @param reader
 * @param factory
 * @todo Implement constructor and implement DI
 */
SceneCreator::SceneCreator(std::unique_ptr<ISceneFileReader> reader,
                           std::unique_ptr<SceneObjectFactory> factory) {
  throw std::runtime_error(
      "Not Implemented: This method is not implemented yet (3DViewer 1.0).");
}

std::shared_ptr<models::SceneObject> SceneCreator::createObject(
    std::string &&filename) {
  auto object = factory->create(reader->read(filename));
  return object;
}

}  // namespace services
