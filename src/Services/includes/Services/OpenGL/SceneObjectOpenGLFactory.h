#pragma once
#include <Services/OpenGL/SceneObjectOpenGL.h>
#include <Services/SceneObjectFactory.h>

namespace opengl {

class SceneObjectOpenGLFactory final : public services::SceneObjectFactory {
 public:
  SceneObjectOpenGLFactory() = default;
  std::shared_ptr<models::SceneObject> create(
      services::SceneFileData data) override;
};

}  // namespace opengl