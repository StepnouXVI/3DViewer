#include <Domain/Settings.h>
// #include "SceneSettings.h"
#include <stdexcept>

namespace Domain {

/**
 * @brief Initializes the default settings of the scene
 *
 */
SceneSettings::SceneSettings() {
  displayType_.ProjectionType = ProjectionType::CENTRAL;
  displayType_.ObjDisplayType = ObjectsDisplayType::SOLID;
  displayType_.Shader = ShadersType::NONE;
  displayType_.RayTracing = RayTracingMode::OFF;
  displayType_.BackgroundDisplayType = BackgroundDisplayType::ABSENT;
  floorSettings_.Color = QVector4D(0.2, 0.2, 0.2, 1);
  floorSettings_.DisplayType = FloorDisplayType::ABSENT;
  floorSettings_.ShowGrid = false;
  vertexSettings_.Type = VertexDisplayType::CIRCLE;
  vertexSettings_.Color = QVector4D(1.0, 1.0, 1.0, 1);
  vertexSettings_.PointSize = 1;
  edgeSettings_.Type = EdgeDisplayType::SOLID;
  edgeSettings_.Color = QVector4D(1.0, 0.0, 0.0, 1);
  edgeSettings_.PointSize = 1;
}

/**
 * @brief Returns the scene settings
 *
 * @return SceneSettings&
 */
SceneSettings& SceneSettings::GetInstance() {
  static SceneSettings instance;
  return instance;
}



/**
 * @brief Returns the scene display settings
 *
 * @return SceneDisplaySettings&
 */
SceneDisplaySettings& SceneSettings::GetDisplaySettings() {
  return displayType_;
}

/**
 * @brief Returns the floor settings
 *
 * @return FloorSettings&
 */
FloorSettings& SceneSettings::GetFloorSettings() { return floorSettings_; }

/**
 * @brief Returns the vertex settings
 *
 * @return VertexSettings&
 */
VertexSettings& SceneSettings::GetVertexSettings() { return vertexSettings_; }

/**
 * @brief Returns the edge settings
 *
 * @return EdgeSettings&
 */
EdgeSettings& SceneSettings::GetEdgeSettings() { return edgeSettings_; }

}  // namespace models
