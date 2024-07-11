#pragma once
#include <Core/SceneDrawer.h>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <vector>

class SceneObject
{
    private:
    QMatrix4x4 _model;
    QOpenGLBuffer _vertexBuffer;
    QOpenGLBuffer _indexBuffer;

    public:
    SceneObject();
    SceneObject(const QMatrix4x4& model, const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    QMatrix4x4 model() const;
    void setModel(const QMatrix4x4& model);
};

