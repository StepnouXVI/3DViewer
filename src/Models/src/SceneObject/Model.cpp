
#include "SceneObject/Model.h"

#include <stdexcept>

namespace models {

/**
 * @brief This method is responsible for drawing the model.
 * @warning This method is not implemented yet (3DViewer 1.0).
 * @todo Implement the drawing logic for the model.
 */
void Model::draw(ISceneDrawer&) {
  throw std::runtime_error(
      "Not Implemented: This method is not implemented yet (3DViewer 1.0).");
}

/**
 * @brief This method sets the name of the model.
 * @warning This method is not implemented yet (3DViewer 1.0).
 * @todo Implement the logic to set the name of the model.
 */
void Model::setName(const std::string&) {
  throw std::runtime_error(
      "Not Implemented: This method is not implemented yet (3DViewer 1.0).");
}

/**
 * @brief This method returns the name of the model.
 * @warning This method is not implemented yet (3DViewer 1.0).
 * @todo Implement the logic to retrieve the name of the model.
 */
std::string Model::getName() const {
  throw std::runtime_error(
      "Not Implemented: This method is not implemented yet (3DViewer 1.0).");
}

}  // namespace models
