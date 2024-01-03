#include "Scene.h"

namespace models {

/**
 * @brief Add model to scene
 *
 * @param model
 */
void Scene::addModel(SceneObjectPtr model) { models_.push_back(model); }

std::vector<SceneObjectPtr>& Scene::getSceneModels() { return models_; }

}  // namespace models