#pragma once
#include <Domain/ISceneDrawer.h>

namespace Domain
{
class IDrawable
{
  public:
    virtual void Draw(ISceneDrawer &) = 0;
    virtual QMatrix4x4& Model() const = 0;
};
} // namespace Domain