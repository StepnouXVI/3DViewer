#pragma once
#include <DTO/Edge.h>
#include <DTO/TransformMatrix.h>
#include <DTO/Vertex.h>
#include <DTO/VisualProperty.h>
#include <Models/SceneObject/SceneObject.h>

#include <string>
#include <vector>

namespace models {

/**
 * @brief Model present itself files scene objects.
 * @warning This class is not implemented yet (3DViewer 1.0).
 * @todo Implement model and logic define area of it (detect loop graph / check
 * files mark)
 */
class Model final : public SceneObject {
 private:
  std::string name_;

 public:
  void draw(ISceneDrawer&) override;
  void setName(const std::string&);
  std::string getName() const;
  //    ~Model();
};

}  // namespace models