#include <Controllers/TransformableController.h>

#include <Services/TransformBuilder.h>

#include <stdexcept>

namespace controllers {

/**
 * @brief Scale the object by the provided factor.
 * @param factor The scaling factor.
 */
void TransformableController::scaleObject(dto::Point3D&& factor) {
  auto transformableObject = getTransformableObject();
  if (transformableObject) {
    auto transformMatrix = services::TransformBuilder::buildScaleMatrix(factor);
    transformableObject->transform(transformMatrix);
    draw(drawer_);
  }
}

/**
 * @brief Rotate the object by the provided angles.
 * @param angles The rotation angles.
 */
void TransformableController::rotateObject(dto::Point3D&& angles) {
  auto transformableObject = getTransformableObject();
  if (getTransformableObject()) {
    auto transformMatrix =
        services::TransformBuilder::buildRotateMatrix(angles);
    transformableObject->transform(transformMatrix);
    draw(drawer_);
  }
}

/**
 * @brief Move the object by the provided point.
 * @param angles The rotation angles.
 */
void TransformableController::moveObject(dto::Point3D&& point) {
  auto transformableObject = getTransformableObject();
  if (transformableObject) {
    auto transformMatrix = services::TransformBuilder::buildMoveMatrix(point);
    transformableObject->transform(transformMatrix);
    draw(drawer_);
  }
}

}  // namespace controllers
