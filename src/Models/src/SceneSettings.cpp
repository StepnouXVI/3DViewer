#include <Models/SceneSettings.h>
// #include "SceneSettings.h"
#include <stdexcept>

namespace models {

/**
 * @brief Initializes the default settings of the scene
 *
 */
SceneSettings::SceneSettings() {
  displayType_.projectionType = ProjectionType::CENTRAL;
  displayType_.objDisplayType = ObjectsDisplayType::WIREFRAME;
  displayType_.shader = ShadersType::NONE;
  displayType_.rayTracing = RayTracingMode::OFF;
  displayType_.backgroundDisplayType = BackgroundDisplayType::ABSENT;
  floorSettings_.color = dto::Color(0.0, 0.0, 0.0, 0.5);
  floorSettings_.displayType = FloorDisplayType::ABSENT;
  floorSettings_.showGrid = false;
  vertexSettings_.type = VertexDisplayType::NONE;
  vertexSettings_.color = dto::Color(1.0, 1.0, 1.0, 0.5);
  vertexSettings_.pointSize = 1;
  edgeSettings_.type = EdgeDisplayType::SOLID;
  edgeSettings_.color = dto::Color(1.0, 0.0, 0.0, 0.5);
  edgeSettings_.pointSize = 1;
}

/**
 * @brief Returns the scene settings
 *
 * @return SceneSettings&
 */
SceneSettings& SceneSettings::getInstance() {
  static SceneSettings instance;
  return instance;
}

/**
 * @brief Returns the light sources
 *
 * @return const std::vector<LightSource>&
 */
const std::vector<LightSource>& SceneSettings::getLights() { return lights_; }

/**
 * @brief Adds light source
 *
 * @param light
 */
void SceneSettings::addLightSource(LightSource&& light) {
  lights_.push_back(std::move(light));
}

/**
 * @brief Removes light source
 * @warning This method is not implemented yet (3DViewer 1.0).
 * @todo Implement the logic to remove light source (need implement operator= in
 * LightSource class)
 * @param light
 */
void SceneSettings::removeLightSource(LightSource&& light) {
  throw std::runtime_error(
      "Not Implemented: This method is not implemented yet (3DViewer 1.0).");
}

/**
 * @brief Returns the scene display settings
 *
 * @return SceneDisplaySettings&
 */
SceneDisplaySettings& SceneSettings::getDisplaySettings() {
  return displayType_;
}

/**
 * @brief Returns the floor settings
 *
 * @return FloorSettings&
 */
FloorSettings& SceneSettings::getFloorSettings() { return floorSettings_; }

/**
 * @brief Returns the vertex settings
 *
 * @return VertexSettings&
 */
VertexSettings& SceneSettings::getVertexSettings() { return vertexSettings_; }

/**
 * @brief Returns the edge settings
 *
 * @return EdgeSettings&
 */
EdgeSettings& SceneSettings::getEdgeSettings() { return edgeSettings_; }

}  // namespace models
