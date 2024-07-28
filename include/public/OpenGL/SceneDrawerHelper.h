
#pragma once

#include <QOpenGLShader>
#include <Domain/ISceneObject.h>
#include <Domain/Camera.h>

namespace OpenGL
{
class SceneDrawerHelper
{
  protected:
    static void AddShader(QOpenGLShaderProgram &program, QOpenGLShader::ShaderTypeBit type, const QString &shaderPath);
    static void AddShaders(QOpenGLShaderProgram &program, const QString &vertex, const QString &geom,
                           const QString &frag);
    static void AddShaders(QOpenGLShaderProgram &program, const QString &vertex, const QString &frag);
    static void SetUpData(QOpenGLShaderProgram &program, Domain::ISceneObject &);
    static void UnSetData(QOpenGLShaderProgram &program, Domain::ISceneObject &);
    static void SetMVP(QOpenGLShaderProgram &program, Domain::Camera&, Domain::ISceneObject &);
};
} // namespace OpenGl
