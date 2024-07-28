#pragma once
#include <Domain/ISceneObject.h>
#include <Domain/Vertex.h>
#include <vector>

namespace OpenGL
{

class SceneObject : public Domain::ISceneObject
{
public:
    SceneObject(const std::vector<Domain::Vertex>& vertices,
                const std::vector<unsigned int>& indices,
                const Domain::TextureMapsPtr textureMaps = nullptr,
                const Domain::PBRMaterialPtr material = nullptr);

    int EdgeCount() const override;
    QMatrix4x4& Model() const override;
    Buffer& VertexBuffer() override;
    Buffer& EdgeBuffer() override;
    VertexArray& VertexArrayObject() override;

    void AddChildren(Domain::ISceneObjectPtr child) override;

    const Domain::TextureMapsPtr TextureMaps() const override;
    const Domain::PBRMaterialPtr Material() const override;

    void ApplyTransform(Domain::Transform&) override;

    void Draw(Domain::ISceneDrawer& ) override;

private:
    VertexArray _vertexArray;
    Buffer _vertexBuffer;
    Buffer _edgeBuffer;

    QMatrix4x4 _model;
    int _edgeCount;

    std::vector<Domain::ISceneObjectPtr> _children;

    const Domain::TextureMapsPtr _textureMaps;
    const Domain::PBRMaterialPtr _material;
};

} // namespace OpenGL

