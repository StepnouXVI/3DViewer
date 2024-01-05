#pragma once
#include <Models/SceneObject/SceneObject.h>
#include <Services/SceneFileData.h>

namespace services {

struct NormalizationParameters {
  double min;
  double max;
  double DxStep;
  double DyStep;
};

class SceneObjectFactory {
 public:
  //    SceneObjectFactory() = default;
  //  /**
  //   * @brief Need for creation atomic SceneObject, which have a parent -
  //   SceneModel(obj file).
  //   * @warning This method is not implemented yet (3DViewer 1.0).
  //   * @todo Implement logic with models.
  //   * @param data - Data about SceneObject
  //   * @param parent - Parent (Model)
  //   * @return models::SceneObject
  //   */
  //  virtual models::SceneObject create(const SceneFileData& data,
  //                                     const models::SceneObject& parent);

  /**
   * @brief Need for creation complex object: scene or model
   *
   * @param data - Data from file
   * @return models::SceneObject
   */
  virtual std::shared_ptr<models::SceneObject> create(SceneFileData data);
};

}  // namespace services
