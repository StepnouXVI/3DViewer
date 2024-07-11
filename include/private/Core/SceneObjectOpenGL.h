#pragma once

#include <QOpenGLBuffer>
#include <QVector3D>
#include <memory>
#include <QMatrix4x4>

class SceneObject {
 public:
  using Buffer = QOpenGLBuffer;

 public:
  QMatrix4x4 _model = QMatrix4x4();
  Buffer indexBuffer;
  Buffer vertexBuffer;

 public:
  explicit SceneObject();
  QMatrix4x4 getModelMatrix() const;

};
