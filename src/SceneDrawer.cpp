
#include <Core/SceneDrawer.h>
#include <Core/ShaderPaths.h>

#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QStyle>
#include <QVector3D>
#include <QWidget>
#include <iostream>

CustomQOpenGLWidget::CustomQOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    view_.lookAt(QVector3D(2, 2, 2), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    setProjection();
}

void CustomQOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    LoadShaders();
    glEnable(GL_CULL_FACE);
    glClearColor(settings_.floorSettings_.color.r, settings_.floorSettings_.color.g, settings_.floorSettings_.color.b,
                 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void CustomQOpenGLWidget::resizeGL(int width, int height)
{
    QOpenGLWidget::resizeGL(width, height);
    aspectRatio_ = width / (float)height;
    setProjection();
}

void CustomQOpenGLWidget::setProjection()
{
    if (settings_.displayType_.projectionType == models::ProjectionType::PARALLEL)
    {
        projection_.ortho(-1.f, 1.f, -1.f / aspectRatio_, 1.f / aspectRatio_, 0.1f, 100.0f);
    }
    else
    {
        projection_.perspective(90, aspectRatio_, 0.1f, 100.0f);
    }
}

void CustomQOpenGLWidget::paintGL()
{
    if (currentObject == nullptr)
        return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setProjection();

    glClearColor(settings_.floorSettings_.color.r, settings_.floorSettings_.color.g, settings_.floorSettings_.color.b,
                 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (settings_.vertexSettings_.type != models::VertexDisplayType::NONE)
    {
        drawVertex(*currentObject);
    }
    if (settings_.edgeSettings_.type == models::EdgeDisplayType::DOTTED)
    {
        drawDottedEdges(*currentObject);
    }
    else
    {
        drawEdges(*currentObject);
    }
    drawFaces(*currentObject);
}

static QVector4D color_from_settings(const Color &color)
{
    return QVector4D(color.r, color.g, color.b, color.a);
}

const QString SHADER_ERROR("ShaderCompilationError: ");

void CustomQOpenGLWidget::AddShader(QOpenGLShaderProgram &program, QOpenGLShader::ShaderTypeBit type,
                                    const QString &shaderPath)
{
    auto file = QFile(shaderPath);
    if(!file.exists())
        std::cout << "File not exists" << std::endl;

    if (!program.addShaderFromSourceFile(type, shaderPath))
    {
        throw std::runtime_error((SHADER_ERROR + shaderPath).toStdString());
    }
}

void CustomQOpenGLWidget::AddShader(QOpenGLShaderProgram &program, const QString &vertexShader,
                                    const QString &fragmentShader)
{
    AddShader(program, QOpenGLShader::Vertex, vertexShader);
    AddShader(program, QOpenGLShader::Fragment, fragmentShader);
    program.link();
}

void CustomQOpenGLWidget::AddShader(QOpenGLShaderProgram &program, const QString &vertex, const QString &geom,
                                    const QString &frag)
{
    AddShader(program, QOpenGLShader::Vertex, vertex);
    AddShader(program, QOpenGLShader::Geometry, geom);
    AddShader(program, QOpenGLShader::Fragment, frag);
    program.link();
}

void CustomQOpenGLWidget::LoadShaders()
{
    AddShader(edgeProgram_, EDGE_VERT_SHADER, EDGE_GEOM_SHADER, EDGE_FRAG_SHADER);
    AddShader(dottedEdgesProgram_, EDGES_DOTTED_VERT_SHADER, EDGES_DOTTED_FRAG_SHADER);
    AddShader(faceProgram_, FACE_VERT_SHADER, FACE_FRAG_SHADER);
    AddShader(faceWithTextureProgram_, FACE_WITH_TEXTURE_VERT_SHADER, FACE_WITH_TEXTURE_FRAG_SHADER);
    AddShader(skyBoxProgram_, SKY_BOX_VERT_SHADER, SKY_BOX_FRAG_SHADER);
    AddShader(vertexProgram_, VERTEX_VERT_SHADER, VERTEX_GEOM_SHADER, VERTEX_FRAG_SHADER);
}

void CustomQOpenGLWidget::setAttributesWithoutTexture(ShaderProgram &program)
{
    int vertLoc = program.attributeLocation("position");
    program.enableAttributeArray(vertLoc);
    program.setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(QVector3D));
}
void CustomQOpenGLWidget::setMVP(ShaderProgram &program, Object &obj)
{
    program.setUniformValue("model", obj.getModelMatrix());
    program.setUniformValue("view", view_);
    program.setUniformValue("projection", projection_);
}

void CustomQOpenGLWidget::drawFaces(Object &obj)
{
    faceProgram_.bind();
    obj.vertexBuffer.bind();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    setMVP(faceProgram_, obj);
    setAttributesWithoutTexture(faceProgram_);
    faceProgram_.setUniformValue("PointColor", QVector4D(0.0f, 0.f, 1.f, 1.0f));


    obj.indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, obj.indexBuffer.size(), GL_UNSIGNED_INT, 0);

    faceProgram_.release();
    obj.vertexBuffer.release();
    obj.indexBuffer.release();
}
void CustomQOpenGLWidget::drawEdges(Object &obj)
{
    obj.indexBuffer.bind();
    obj.vertexBuffer.bind();

    edgeProgram_.bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    setAttributesWithoutTexture(edgeProgram_);
    setMVP(edgeProgram_, obj);

    edgeProgram_.setUniformValue("PointColor", color_from_settings(settings_.edgeSettings_.color));
    edgeProgram_.setUniformValue("ViewportInvSize", resolution_);
    edgeProgram_.setUniformValue("Thickness", settings_.edgeSettings_.pointSize);

    glDrawElements(GL_TRIANGLES, obj.indexBuffer.size(), GL_UNSIGNED_INT, 0);

    edgeProgram_.release();

    obj.vertexBuffer.release();
    obj.indexBuffer.release();
}
void CustomQOpenGLWidget::drawDottedEdges(Object &obj)
{
    obj.indexBuffer.bind();
    obj.vertexBuffer.bind();

    dottedEdgesProgram_.bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    setAttributesWithoutTexture(dottedEdgesProgram_);
    setMVP(dottedEdgesProgram_, obj);

    dottedEdgesProgram_.setUniformValue("PointColor", color_from_settings(settings_.edgeSettings_.color));

    dottedEdgesProgram_.setUniformValue("Resolution", resolution_);
    dottedEdgesProgram_.setUniformValue("DashSize", 5.f);
    dottedEdgesProgram_.setUniformValue("GapSize", 25.f);

    glDrawElements(GL_TRIANGLES, obj.indexBuffer.size(), GL_UNSIGNED_INT, 0);

    dottedEdgesProgram_.release();

    obj.vertexBuffer.release();
    obj.indexBuffer.release();
}
void CustomQOpenGLWidget::drawVertex(Object &obj)
{
    vertexProgram_.bind();
    obj.indexBuffer.bind();
    obj.vertexBuffer.bind();

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    setMVP(vertexProgram_, obj);
    setAttributesWithoutTexture(vertexProgram_);

    vertexProgram_.setUniformValue("PointColor", color_from_settings(settings_.vertexSettings_.color));

    vertexProgram_.setUniformValue("PointSize", settings_.vertexSettings_.pointSize);
    vertexProgram_.setUniformValue("RoundPoint", settings_.vertexSettings_.type == models::VertexDisplayType::CIRCLE);

    glDrawElements(GL_POINTS, obj.indexBuffer.size(), GL_INT, 0);

    obj.vertexBuffer.release();
    obj.indexBuffer.release();
    vertexProgram_.release();
}

void CustomQOpenGLWidget::draw(SceneObject &obj)
{
    currentObject = &obj;
    update();
}
