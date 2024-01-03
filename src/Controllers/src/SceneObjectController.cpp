#include <SceneObjectController.h>

#include <stdexcept>

namespace controllers {

/**
 * @brief Method for injection of a child controller.
 * @warning Inject could be called only once!.
 * @throw std::runtime_error If you are trying to put this into an object.
 * @param childController The child controller to inject.
 */
void SceneObjectController::injectChild(
    SceneObjectControllerPtr childController) {
  if (this == childController.get()) {
    throw std::runtime_error(
        "Circular reference: you are trying to put yourself into an object!");
  }
  if (!childController_) {
    childController_ = childController;
  }
}
/**
 * @brief Injection of a model to controller.
 * @param model The model to inject.
 */
void SceneObjectController::injectModel(models::SceneObjectPtr model) {
  sceneObject_ = model;
}

/**
 * @brief Select the next object in the scene.
 * @warning This method is not implemented yet (3DViewer 1.0).
 * @todo Implement the logic to select the next object.
 */
void SceneObjectController::setActiveChildIdx(int idx) {
  if (childController_) {
    childController_->injectModel(
        sceneObject_->getChildren()->at(++currentChildIndex_));
  }
}

/**
 * @brief Set the visual property of the scene object.
 * @param property The visual property to set.
 */
void SceneObjectController::setVisualProperty(dto::VisualProperty&& property) {
  sceneObject_->setVisualProperty(std::move(property));
}

/**
 * @brief Remove the texture from the scene object.
 * @warning This method is not implemented yet (3DViewer 1.0).
 * @todo Implement the logic to remove the texture from the scene object.
 */
void SceneObjectController::removeTexture() {
  throw std::runtime_error(
      "Not Implemented: This method is not implemented yet (3DViewer 1.0).");
}

void SceneObjectController::draw(models::ISceneDrawerPtr drawer) {
  drawer->draw(*sceneObject_);
}

std::shared_ptr<models::TransformableObject>
SceneObjectController::getTransformableObject() {
  return sceneObject_;
}

std::shared_ptr<models::TransformableObject>
SceneObjectController::getCurrentChild() {
  throw std::runtime_error(
      "Not Implemented: This method is not implemented yet (3DViewer 1.0).");
}

models::ChildrenObjects SceneObjectController::getChildren() {
  throw std::runtime_error(
      "Not Implemented: This method (SceneObjectController::getChildren) is "
      "not implemented yet (3DViewer 1.0).");
}

/**
 * @todo Remove in the future
 * @return
 */
std::shared_ptr<models::SceneObject> SceneObjectController::getSceneObject() {
  return sceneObject_;
}

}  // namespace controllers
