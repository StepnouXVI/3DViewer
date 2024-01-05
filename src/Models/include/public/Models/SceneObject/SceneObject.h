#pragma once

#include <DTO/Edge.h>
#include <DTO/TransformMatrix.h>
#include <DTO/Vertex.h>
#include <DTO/VisualProperty.h>
#include <Models/ISceneDrawer.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <Models/TransformableObject.h>

namespace models {

class SceneObject;
using SceneObjectPtr = std::shared_ptr<SceneObject>;

using ChildrenObjects = std::vector<SceneObjectPtr>;
using Vertices = std::vector<dto::Vertex>;
using Edges = std::vector<dto::Edge>;

class SceneObject : public TransformableObject {
 public:
  SceneObject() = default;
  SceneObject(Vertices &&, Edges &&);
  virtual void draw(ISceneDrawer &);
  void addChild(SceneObjectPtr);
  std::optional<ChildrenObjects> getChildren();
  void setVertices(Vertices &&);
  void setEdges(Edges &&);
  [[nodiscard]] virtual const dto::TransformMatrix &getModelMatrix() const;
  [[nodiscard]] const Vertices &getVertices() const;
  [[nodiscard]] const Edges &getEdges() const;

  void setVisualProperty(dto::VisualProperty &&);
  const dto::VisualProperty &getVisualProperty();

  virtual ~SceneObject(){};

 protected:
  ChildrenObjects children_;

 private:
  Vertices vertices_;
  Edges edges_;

  dto::VisualProperty visualProperty_;
};

}  // namespace models
