#include <Domain/Camera.h>
#include <Domain/Vertex.h>
#include <OpenGL/SceneDrawerHelper.h>


using namespace OpenGL;
using namespace Domain;

const QString SHADER_ERROR("ShaderCompilationError: ");

void SceneDrawerHelper::AddShaders(QOpenGLShaderProgram &program, const QString &vertex, const QString &geom,
                                   const QString &frag)
{
    AddShader(program, QOpenGLShader::Vertex, vertex);
    AddShader(program, QOpenGLShader::Geometry, geom);
    AddShader(program, QOpenGLShader::Fragment, frag);
    program.link();
    program.bind();
}

void SceneDrawerHelper::AddShaders(QOpenGLShaderProgram &program, const QString &vertexShader,
                                   const QString &fragmentShader)
{
    AddShader(program, QOpenGLShader::Vertex, vertexShader);
    AddShader(program, QOpenGLShader::Fragment, fragmentShader);
    program.link();
    program.bind();
}

void SceneDrawerHelper::AddShader(QOpenGLShaderProgram &program, QOpenGLShader::ShaderTypeBit type,
                                  const QString &shaderPath)
{
    if (!program.addShaderFromSourceFile(type, shaderPath))
    {
        throw std::runtime_error((SHADER_ERROR + shaderPath).toStdString());
    }
}

void SceneDrawerHelper::SetUpData(QOpenGLShaderProgram &program, ISceneObject &object)
{
    object.VertexArrayObject().bind();
    object.VertexBuffer().bind();
    object.EdgeBuffer().bind();

    program.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(Vertex));
    program.enableAttributeArray(0);

    program.setAttributeBuffer(1, GL_FLOAT, offsetof(Vertex, Normal), 3, sizeof(Vertex));
    program.enableAttributeArray(1);

    program.setAttributeBuffer(2, GL_FLOAT, offsetof(Vertex, TexCoords), 2,
                              sizeof(Vertex));
    program.enableAttributeArray(2);

    program.setAttributeBuffer(3, GL_FLOAT, offsetof(Vertex, Tangent), 3, sizeof(Vertex));
    program.enableAttributeArray(3);

    program.setAttributeBuffer(4, GL_FLOAT, offsetof(Vertex, BiTangent), 3, sizeof(Vertex));
    program.enableAttributeArray(4);
}

void SceneDrawerHelper::UnSetData(QOpenGLShaderProgram &program, ISceneObject &object)
{
    program.disableAttributeArray(0);
    program.disableAttributeArray(1);
    program.disableAttributeArray(2);
    program.disableAttributeArray(3);
    program.disableAttributeArray(4);

    object.VertexArrayObject().release();
    object.VertexBuffer().release();
    object.EdgeBuffer().release();
}

void SceneDrawerHelper::SetMVP(QOpenGLShaderProgram &program, Camera &camera, ISceneObject &obj)
{
    program.setUniformValue("projection", camera.Projection());
    program.setUniformValue("view", camera.View());
    program.setUniformValue("model", obj.Model());
}

