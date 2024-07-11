#include <Core/SceneSettings.h>
// #include "SceneSettings.h"
#include <stdexcept>

namespace models {

/**
 * @brief Initializes the default settings of the scene
 *
 */
SceneSettings::SceneSettings() {
  displayType_.projectionType = ProjectionType::CENTRAL;
  displayType_.objDisplayType = ObjectsDisplayType::SOLID;
  displayType_.shader = ShadersType::NONE;
  displayType_.rayTracing = RayTracingMode::OFF;
  displayType_.backgroundDisplayType = BackgroundDisplayType::ABSENT;
  floorSettings_.color = Color(0.2, 0.2, 0.2, 1);
  floorSettings_.displayType = FloorDisplayType::ABSENT;
  floorSettings_.showGrid = false;
  vertexSettings_.type = VertexDisplayType::CIRCLE;
  vertexSettings_.color = Color(1.0, 1.0, 1.0, 1);
  vertexSettings_.pointSize = 1;
  edgeSettings_.type = EdgeDisplayType::SOLID;
  edgeSettings_.color = Color(1.0, 0.0, 0.0, 1);
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
