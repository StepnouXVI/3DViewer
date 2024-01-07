#include <Controllers/SceneController.h>
#include <Services/SceneFileOBJReader.h>

#include <stdexcept>

namespace controllers {

/**
 * @brief Temporary constructor for DI
 * @todo Remove it
 */
SceneController::SceneController(models::ISceneDrawerPtr& drawer)
    : TransformableController(drawer) {
  sceneCreator_ = std::make_unique<services::SceneCreator>();
}

/**
 * @brief Constructor for SceneController.
 * Initializes the scene creator with the specified reader and factory.
 * @warning This constructor is not implemented yet (3DViewer 1.0).
 */
// SceneController::SceneController(std::unique_ptr<services::SceneCreator>
// sceneCreator) {
//     throw std::runtime_error("Not Implemented: This method is not implemented
//     yet (3DViewer 1.0).");
// }

/**
 * @brief Set the active child index
 * @todo Internal TransformableController Iterator
 */
void SceneController::setActiveChildIdx(int idx) {
  if (sceneModelController_) {
    auto sceneObject = scene_.getSceneModels().at(idx);
    sceneModelController_->injectModel(scene_.getSceneModels().at(idx));
  }
}

/**
 * @brief Load a model with the specified name and add it to the scene.
 * @param modelName The name of the model to load.
 */
std::shared_ptr<models::SceneObject> SceneController::loadModel(
    std::string modelName) {
  auto model = sceneCreator_->createObject(std::move(modelName));
  scene_.addModel(model);
  return model;
}

void SceneController::draw(models::ISceneDrawerPtr drawer) {
  drawer->draw(scene_);
}

std::shared_ptr<models::TransformableObject>
SceneController::getTransformableObject() {
  return getCurrentChild();
  //    throw std::runtime_error("Not Implemented: This method is not
  //    implemented yet (3DViewer 1.0).");
}

/**
 * @brief Get the children of the scene
 * @return
 */
models::ChildrenObjects SceneController::getChildren() {
  return scene_.getSceneModels();
}

std::shared_ptr<models::TransformableObject>
SceneController::getCurrentChild() {
  return sceneModelController_->getSceneObject();
  throw std::runtime_error(
      "Not Implemented: This method (SceneObjectController::getCurrentChild) "
      "is not implemented yet (3DViewer 1.0).");
}

}  // namespace controllers
