#include <Services/SceneObjectFactory.h>

namespace services {

std::shared_ptr<models::SceneObject> SceneObjectFactory::create(
    SceneFileData data) {
  models::Vertices vertices(data.v_coord.size());
  for (int idx = 0; idx < data.v_coord.size(); ++idx) {
    vertices[idx] = data.v_coord[idx];
  }

  auto result = std::make_shared<models::SceneObject>(std::move(vertices),
                                                      std::move(data.faces));
  return result;
}

}  // namespace services