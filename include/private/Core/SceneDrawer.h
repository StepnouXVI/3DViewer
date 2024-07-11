#pragma once

#include <Core/SceneSettings.h>
#include <Core/SceneObjectOpenGL.h>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QPaintEvent>
#include <QPainter>

class CustomQOpenGLWidget : public QOpenGLWidget,
                            protected QOpenGLFunctions_4_1_Core
                            {
  Q_OBJECT

 public:
  CustomQOpenGLWidget(QWidget *parent = nullptr);

  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  void draw(SceneObject&);

 public:
  using Buffer = QOpenGLBuffer;
  using ShaderProgram = QOpenGLShaderProgram;
  using Matrix = QMatrix4x4;
  using Object = SceneObject;

 private:
  Object *currentObject = new SceneObject();
  QVector2D resolution_;

  Matrix view_;
  Matrix projection_;
  double aspectRatio_ = 16.0 / 9.0;

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

  void setProjection();
  void setAttributesWithoutTexture(ShaderProgram &program);
  void setMVP(ShaderProgram &program, Object &obj);
  void drawFaces(Object &obj);
  void drawEdges(Object &obj);
  void drawDottedEdges(Object &obj);
  void drawVertex(Object &obj);
};
