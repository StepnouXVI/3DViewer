#pragma once
#include <Models/SceneObject/SceneObject.h>

#include <QOpenGLBuffer>
#include <QVector3D>
#include <memory>

namespace opengl {

class SceneObjectOpenGL : public models::SceneObject {
 public:
  using Buffer = QOpenGLBuffer;

 public:
  Buffer indexBuffer;
  Buffer vertexBuffer;

 public:
  explicit SceneObjectOpenGL(const models::SceneObject& obj);

 private:
  void convertEdgesToIndexes(std::vector<int>& indexes);
  void convertVertexesToPoints(std::vector<QVector3D>& points);
};

}  // namespace opengl
