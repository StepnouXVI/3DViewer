#pragma once
#include <Models/SceneSettings.h>

#include <QWidget>

class SwitchMenuController : public QObject {
  enum class Texture { OFF, ON };

  enum class FloorGrid { OFF, ON };

  enum class EdgeProperties { HARD, SOFT };

  models::ProjectionType activeProjectionType_ =
      models::ProjectionType::PARALLEL;
  models::ObjectsDisplayType activeObjDisplayType_ =
      models::ObjectsDisplayType::SOLID;

  models::ShadersType activeShader_ = models::ShadersType::NONE;
  models::RayTracingMode activeRayTracing_ = models::RayTracingMode::OFF;

  models::EdgeDisplayType activeEdgeType_ = models::EdgeDisplayType::SOLID;
  EdgeProperties activeEdgeProperties_ = EdgeProperties::HARD;
  models::VertexDisplayType activeVertexDisplayType_ =
      models::VertexDisplayType::NONE;

  models::BackgroundDisplayType activeBackground_ =
      models::BackgroundDisplayType::ABSENT;
  FloorGrid activeFloorGrid_ = FloorGrid::OFF;
  models::FloorDisplayType activeFloor_ = models::FloorDisplayType::ABSENT;

  models::Lighting activeLighting_ = models::Lighting::NONE;
  Texture activeTexture_ = Texture::OFF;

 public:
  SwitchMenuController();

  void setActiveProjectionType(int projectionType);

  void setActiveObjDisplayType(int objDisplayType);

  void setActiveShader(int shader);

  void setActiveRayTracing(int rayTracing);

  void setActiveEdgeType(int edgeType);

  void setActiveEdgeProperties(int edgeProperties);

  void setActiveVertexDisplayType(int vertexDisplayType);

  void setActiveBackground(int background);

  void setActiveFloorGrid(int floorGrid);

  void setActiveFloor(int floor);

  void setActiveLighting(int lighting);

  void setActiveTexture(int texture);
};