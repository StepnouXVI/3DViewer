#pragma once
#include <Models/ISceneDrawer.h>
#include <Models/SceneSettings.h>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include "Services/OpenGL/SceneObjectOpenGL.h"

namespace opengl {

class ShaderDrawer : public models::ISceneDrawer, protected QOpenGLFunctions {
 public:
  ShaderDrawer(QOpenGLContext *context);
  void draw(models::TransformableObject &) override;
  ~ShaderDrawer();

 public:
  using Buffer = QOpenGLBuffer;
  using ShaderProgram = QOpenGLShaderProgram;
  using Matrix = QMatrix4x4;
  using Object = SceneObjectOpenGL;

 private:
  QVector2D resolution_;

  Matrix view_;
  Matrix projection_;

  // @todo Remove it
  const models::SceneSettings &settings_ = models::SceneSettings::getInstance();
  ShaderProgram edgeProgram_;
  ShaderProgram dottedEdgesProgram_;
  ShaderProgram faceProgram_;
  ShaderProgram faceWithTextureProgram_;
  ShaderProgram skyBoxProgram_;
  ShaderProgram vertexProgram_;

  void AddShaderFromString(QOpenGLShaderProgram &program,
                           QOpenGLShader::ShaderTypeBit type,
                           const QString &shader);
  void AddShader(ShaderProgram &program, QOpenGLShader::ShaderTypeBit type,
                 const QString &shaderPath);
  void AddShader(ShaderProgram &program, const QString &vertex,
                 const QString &frag);
  void AddShader(ShaderProgram &program, const QString &vertex,
                 const QString &geom, const QString &frag);
  void LoadShaders();

  void setAttributesWithoutTexture(ShaderProgram &program);
  void setMVP(ShaderProgram &program, Object &obj);
  void drawFaces(Object &obj);
  void drawEdges(Object &obj);
  void drawDottedEdges(Object &obj);
  void drawVertex(Object &obj);
};

}  // namespace opengl
