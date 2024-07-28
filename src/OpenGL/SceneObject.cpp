#include <Domain/Transform.h>
#include <OpenGL/SceneObject.h>


using namespace Domain;
using namespace OpenGL;

SceneObject::SceneObject(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
                         const Domain::TextureMapsPtr textureMaps, const Domain::PBRMaterialPtr material)
    : _vertexBuffer(QOpenGLBuffer::VertexBuffer), _edgeBuffer(QOpenGLBuffer::IndexBuffer), _model(),
      _edgeCount(indices.size()), _children(), _textureMaps(textureMaps), _material(material)
{
    _vertexArray.create();
    _vertexArray.bind();

    _vertexBuffer.create();
    _vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vertexBuffer.bind();
    _vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(Vertex));

    _edgeBuffer.create();
    _edgeBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _edgeBuffer.bind();
    _edgeBuffer.allocate(indices.data(), indices.size() * sizeof(unsigned int));

    _vertexArray.release();
    _vertexBuffer.release();
    _edgeBuffer.release();
}

int SceneObject::EdgeCount() const
{
    return _edgeCount;
}

QMatrix4x4& SceneObject::Model() const
{
    return _model;
}

QOpenGLBuffer &SceneObject::VertexBuffer()
{
    return _vertexBuffer;
}

QOpenGLBuffer &SceneObject::EdgeBuffer()
{
    return _edgeBuffer;
}

QOpenGLVertexArrayObject &SceneObject::VertexArrayObject()
{
    return _vertexArray;
}

void SceneObject::AddChildren(Domain::ISceneObjectPtr child)
{
    _children.push_back(child);
}

const Domain::TextureMapsPtr SceneObject::TextureMaps() const
{
    return _textureMaps;
}

const Domain::PBRMaterialPtr SceneObject::Material() const
{
    return _material;
}

void SceneObject::ApplyTransform(Transform &transform)
{
    transform.Apply(_model);
    for (auto& child : _children)
    {
        child->ApplyTransform(transform);
    }
}

void SceneObject::Draw(ISceneDrawer &drawer)
{
    drawer.Draw(*this);
    for (auto& child : _children)
    {
        child->Draw(drawer);
    }
}
