#pragma once
#include <Domain/Settings.h>
#include <QOpenGLShader>

namespace Domain
{
class ISceneObject;
class ISceneDrawer
{
  public:
    virtual void Draw(ISceneObject &) = 0;
    virtual void Initialize() = 0;
};
using ISceneDrawerPtr = std::shared_ptr<ISceneDrawer>;
} // namespace Domain