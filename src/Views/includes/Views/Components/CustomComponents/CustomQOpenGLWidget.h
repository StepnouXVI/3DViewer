#pragma once
#include <Models/ISceneDrawer.h>
#include <Models/SceneSettings.h>
#include <Services/OpenGL/SceneObjectOpenGL.h>
#include <Services/SceneFileOBJReader.h>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QPaintEvent>
#include <QPainter>

class CustomQOpenGLWidget : public QOpenGLWidget,
                            protected QOpenGLFunctions,
                            public models::ISceneDrawer {
  Q_OBJECT

 public:
  CustomQOpenGLWidget(QWidget *parent = nullptr);

  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  // QOpenGLContext* getSharedContext();
  std::shared_ptr<models::ISceneDrawer> getShared();

  void draw(models::TransformableObject &) override;

 public:
  using Buffer = QOpenGLBuffer;
  using ShaderProgram = QOpenGLShaderProgram;
  using Matrix = QMatrix4x4;
  using Object = opengl::SceneObjectOpenGL;

 private:
  Object *currentObject = nullptr;
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

  void setProjection();
  void setAttributesWithoutTexture(ShaderProgram &program);
  void setMVP(ShaderProgram &program, Object &obj);
  void drawFaces(Object &obj);
  void drawEdges(Object &obj);
  void drawDottedEdges(Object &obj);
  void drawVertex(Object &obj);
};
