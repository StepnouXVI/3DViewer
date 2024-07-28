#pragma once

#include <Domain/ISceneObject.h>
#include <Domain/ITransformableObject.h>
#include <vector>

namespace Domain
{
class Scene : public ITransformableObject, public IDrawable
{
  private:
    std::vector<ISceneObjectPtr> _objects;
    QMatrix4x4 _model = QMatrix4x4();
    

  public:
    void ApplyTransform(Transform &) override;
    void AddModel(ISceneObjectPtr);
    void Draw(ISceneDrawer &) override;
    QMatrix4x4& Model() override;
};

using ScenePtr = std::shared_ptr<Scene>;
} // namespace Domain
