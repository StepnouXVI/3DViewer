#pragma once
#include <Domain/IDrawable.h>
#include <Domain/ISceneDrawer.h>
#include <Domain/ITransformableObject.h>
#include <Domain/PBRMaterial.h>
#include <Domain/TextureMaps.h>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <memory>
#include <vector>

namespace Domain
{
class ISceneObject : public ITransformableObject, public IDrawable
{
  public:
    using Buffer = QOpenGLBuffer;
    using VertexArray = QOpenGLVertexArrayObject;

  public:
    virtual int EdgeCount() const = 0;
    virtual Buffer &VertexBuffer() = 0;
    virtual Buffer &EdgeBuffer() = 0;
    virtual VertexArray &VertexArrayObject() = 0;

    virtual void AddChildren(std::shared_ptr<ISceneObject>) = 0;

    virtual const TextureMapsPtr TextureMaps() const = 0;

    virtual const PBRMaterialPtr Material() const = 0;
};
using ISceneObjectPtr = std::shared_ptr<ISceneObject>;
} // namespace Domain