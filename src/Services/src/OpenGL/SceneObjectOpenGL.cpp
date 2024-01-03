#include <Services/OpenGL/SceneObjectOpenGL.h>

#include <QVector3D>
#include <iostream>

namespace opengl {

SceneObjectOpenGL::SceneObjectOpenGL(const models::SceneObject &obj)
    : models::SceneObject(obj), indexBuffer(QOpenGLBuffer::IndexBuffer) {
  std::vector<int> indexes = {};
  std::vector<QVector3D> points = {};
  convertEdgesToIndexes(indexes);
  convertVertexesToPoints(points);

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indexes.data(), indexes.size() * sizeof(int));
  indexBuffer.release();

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(points.data(), points.size() * sizeof(QVector3D));
  vertexBuffer.release();
}

void SceneObjectOpenGL::convertEdgesToIndexes(std::vector<int> &indexes) {
  for (const auto &edge : getEdges()) {
    for (const auto &index : edge.v_coord) {
      indexes.push_back(index);
    }
  }
}
void SceneObjectOpenGL::convertVertexesToPoints(
    std::vector<QVector3D> &points) {
  for (const auto &vertex : getVertices()) {
    points.push_back(QVector3D(vertex.coord.x, vertex.coord.y, vertex.coord.z));
  }
}
}  // namespace opengl
