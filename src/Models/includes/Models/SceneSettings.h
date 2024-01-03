#pragma once
#include <DTO/Color.h>
#include <Models/Light/LightSource.h>

#include <utility>
#include <vector>

namespace models {

enum class ProjectionType {
  PARALLEL,
  CENTRAL,
};

enum class ObjectsDisplayType { WIREFRAME, SOLID };

enum class ShadersType { NONE, FLAT, SOFT };

enum class RayTracingMode { OFF, ON };

enum class EdgeDisplayType { SOLID, DOTTED };

enum class VertexDisplayType { NONE, CIRCLE, SQUARE };

enum class FloorDisplayType { COLOR, IMAGE, ABSENT };

enum class BackgroundDisplayType { COLOR, IMAGE, ABSENT };

enum class Lighting { NONE, SIMPLE, DIRECTED, GLOBAL };

struct EdgeSettings {
  EdgeDisplayType type;
  dto::Color color;
  int pointSize;
};

struct VertexSettings {
  VertexDisplayType type;
  dto::Color color;
  int pointSize;
};

struct FloorSettings {
  dto::Color color;
  FloorDisplayType displayType;
  bool showGrid;
};

struct SceneDisplaySettings {
  ProjectionType projectionType;
  ObjectsDisplayType objDisplayType;
  ShadersType shader;
  RayTracingMode rayTracing;
  BackgroundDisplayType backgroundDisplayType;
};

class SceneSettings {
 private:
  SceneSettings();

 public:
  static SceneSettings& getInstance();
  SceneSettings& operator=(const SceneSettings&) = delete;
  SceneSettings(const SceneSettings&) = delete;

  const std::vector<LightSource>& getLights();
  void addLightSource(LightSource&& light);
  void removeLightSource(LightSource&& light);

  SceneDisplaySettings& getDisplaySettings();
  FloorSettings& getFloorSettings();
  VertexSettings& getVertexSettings();
  EdgeSettings& getEdgeSettings();

 public:
  std::vector<LightSource> lights_;
  SceneDisplaySettings displayType_;
  FloorSettings floorSettings_;
  VertexSettings vertexSettings_;
  EdgeSettings edgeSettings_;
};

}  // namespace models
