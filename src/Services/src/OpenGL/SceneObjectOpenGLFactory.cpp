#include "Services/OpenGL/SceneObjectOpenGLFactory.h"

namespace opengl {

std::shared_ptr<models::SceneObject> SceneObjectOpenGLFactory::create(
    services::SceneFileData data) {
  auto object = services::SceneObjectFactory::create(data);
  object = std::make_shared<SceneObjectOpenGL>(*object);
  return object;
}

}  // namespace opengl
