#include <Core/SceneObjectOpenGL.h>

#include <QVector3D>
#include <iostream>

SceneObject::SceneObject()
    :indexBuffer(QOpenGLBuffer::IndexBuffer), vertexBuffer(QOpenGLBuffer::VertexBuffer) {
  // indexes for cube
  std::vector<int> indexes = {
    0, 1, 2, // front
    2, 3, 0,
    3, 2, 6, // right
    6, 7, 3,
    7, 6, 5, // back
    5, 4, 7,
    4, 0, 3, // left
    3, 7, 4,
    5, 1, 6, // top
    6, 2, 5,
    1, 5, 7, // bottom
    7, 6, 4,
    4, 0, 1
  };

  // points for cube
  std::vector<QVector3D> points = {
    QVector3D(-1, -1, -1),
    QVector3D(1, -1, -1),
    QVector3D(1, 1, -1),
    QVector3D(-1, 1, -1),
    QVector3D(-1, -1, 1),
    QVector3D(1, -1, 1),
    QVector3D(1, 1, 1),
    QVector3D(-1, 1, 1)
  };

  _model.setToIdentity();

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indexes.data(), indexes.size() * sizeof(int));
  indexBuffer.release();

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(points.data(), points.size() * sizeof(QVector3D));
  vertexBuffer.release();
}

QMatrix4x4 SceneObject::getModelMatrix() const {
  return _model;
}

