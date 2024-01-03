#include <Models/SceneObject/SceneObject.h>
//#include "SceneObject/SceneObject.h"
#include <iostream>

namespace models {

SceneObject::SceneObject(Vertices &&vertices, Edges &&edges)
    : vertices_(std::move(vertices)), edges_(std::move(edges)) {}

void SceneObject::draw(ISceneDrawer &drawer) { drawer.draw(*this); }

std::optional<ChildrenObjects> SceneObject::getChildren() {
  if (children_.empty()) return std::nullopt;
  return children_;
}

void SceneObject::addChild(SceneObjectPtr child) { children_.push_back(child); }

const dto::TransformMatrix &SceneObject::getModelMatrix() const {
  return modelMatrix_;
}

void SceneObject::setVertices(Vertices &&vertices) {
  vertices_ = std::move(vertices);
}

const Vertices &SceneObject::getVertices() const { return vertices_; }

void SceneObject::setEdges(Edges &&edges) { edges_ = std::move(edges); }

const Edges &SceneObject::getEdges() const { return edges_; }

/**
 * @brief Set the visual property of the scene object.
 * @warning This method is not implemented yet (3DViewer 1.0).
 */
void SceneObject::setVisualProperty(dto::VisualProperty &&property) {
  visualProperty_ = std::move(property);
}

const dto::VisualProperty &SceneObject::getVisualProperty() {
  return visualProperty_;
}

}  // namespace models
