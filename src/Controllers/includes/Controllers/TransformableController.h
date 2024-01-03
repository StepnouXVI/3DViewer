#pragma once

#include <DTO/Point3D.h>
#include <Models/ISceneDrawer.h>
#include <Models/TransformableObject.h>
#include <Services/TransformBuilder.h>

#include <vector>

namespace controllers {

/**
 * @brief Class for transformable objects: scene, model and atomic scene object.
 *
 */
class TransformableController {
 public:
  explicit TransformableController(models::ISceneDrawerPtr& drawer)
      : drawer_(drawer){};
  void scaleObject(dto::Point3D&&);
  void rotateObject(dto::Point3D&&);
  void moveObject(dto::Point3D&&);

  /**
   * @brief Нужен для отрисовки объекта. Спросить у Савватея, нужен ли здесь
   * вообще
   * @todo Переделать все методы draw на shared_ptr
   */
  virtual void draw(models::ISceneDrawerPtr) = 0;

 protected:
  virtual std::shared_ptr<models::TransformableObject>
  getTransformableObject() = 0;

  models::ISceneDrawerPtr& drawer_;
};

using TransformableControllerPtr = std::shared_ptr<TransformableController>;

}  // namespace controllers