#include <Views/TmpControllers/SwitchMenuController.h>

#include <QWidget>

SwitchMenuController::SwitchMenuController() {}

void SwitchMenuController::setActiveProjectionType(int projectionType) {
  activeProjectionType_ = static_cast<models::ProjectionType>(projectionType);
}

void SwitchMenuController::setActiveObjDisplayType(int objDisplayType) {
  activeObjDisplayType_ =
      static_cast<models::ObjectsDisplayType>(objDisplayType);
}

void SwitchMenuController::setActiveShader(int shader) {
  activeShader_ = static_cast<models::ShadersType>(shader);
}

void SwitchMenuController::setActiveRayTracing(int rayTracing) {
  activeRayTracing_ = static_cast<models::RayTracingMode>(rayTracing);
}

void SwitchMenuController::setActiveEdgeType(int edgeType) {
  activeEdgeType_ = static_cast<models::EdgeDisplayType>(edgeType);
}

void SwitchMenuController::setActiveEdgeProperties(int edgeProperties) {
  activeEdgeProperties_ = static_cast<EdgeProperties>(edgeProperties);
}

void SwitchMenuController::setActiveVertexDisplayType(int vertexDisplayType) {
  activeVertexDisplayType_ =
      static_cast<models::VertexDisplayType>(vertexDisplayType);
}

void SwitchMenuController::setActiveBackground(int background) {
  activeBackground_ = static_cast<models::BackgroundDisplayType>(background);
}

void SwitchMenuController::setActiveFloorGrid(int floorGrid) {
  activeFloorGrid_ = static_cast<FloorGrid>(floorGrid);
}

void SwitchMenuController::setActiveFloor(int floor) {
  activeFloor_ = static_cast<models::FloorDisplayType>(floor);
}

void SwitchMenuController::setActiveLighting(int lighting) {
  activeLighting_ = static_cast<models::Lighting>(lighting);
}

void SwitchMenuController::setActiveTexture(int texture) {
  activeTexture_ = static_cast<Texture>(texture);
}
