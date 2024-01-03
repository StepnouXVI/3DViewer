#include <Services/OpenGL/SceneObjectOpenGL.h>
#include <Services/OpenGL/ShaderDrawer.h>
#include <Services/OpenGL/Shaders/ShadersStrings.h>

#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QStyle>
#include <QWidget>
#include <fstream>

namespace opengl {

static QVector4D color_from_settings(const dto::Color &color) {
  return QVector4D(color.r, color.g, color.b, color.a);
}

const QString SHADER_ERROR("ShaderCompilationError: ");

void ShaderDrawer::AddShader(QOpenGLShaderProgram &program,
                             QOpenGLShader::ShaderTypeBit type,
                             const QString &shaderPath) {
  if (!program.addShaderFromSourceFile(type, shaderPath)) {
    throw std::runtime_error((SHADER_ERROR + shaderPath).toStdString());
  }
}

void ShaderDrawer::AddShaderFromString(QOpenGLShaderProgram &program,
                                       QOpenGLShader::ShaderTypeBit type,
                                       const QString &shader) {
  if (!program.addShaderFromSourceCode(type, shader)) {
    throw std::runtime_error((SHADER_ERROR + shader).toStdString());
  }
}

void ShaderDrawer::AddShader(QOpenGLShaderProgram &program,
                             const QString &vertexShader,
                             const QString &fragmentShader) {
  AddShaderFromString(program, QOpenGLShader::Vertex, vertexShader);
  AddShaderFromString(program, QOpenGLShader::Fragment, fragmentShader);
  // AddShader(program, QOpenGLShader::Vertex, vertexShader);
  // AddShader(program, QOpenGLShader::Fragment, fragmentShader);
  program.link();
}

void ShaderDrawer::AddShader(QOpenGLShaderProgram &program,
                             const QString &vertex, const QString &geom,
                             const QString &frag) {
  AddShaderFromString(program, QOpenGLShader::Vertex, vertex);
  AddShaderFromString(program, QOpenGLShader::Geometry, geom);
  AddShaderFromString(program, QOpenGLShader::Fragment, frag);
  // AddShader(program, QOpenGLShader::Vertex, vertex);
  // AddShader(program, QOpenGLShader::Geometry, geom);
  // AddShader(program, QOpenGLShader::Fragment, frag);
  program.link();
}

void ShaderDrawer::LoadShaders() {
  AddShader(edgeProgram_, EdgeVertShader, EdgeGeomShader, EdgeFragShader);
  AddShader(dottedEdgesProgram_, EdgesDottedVertShader, EdgesDottedFragShader);
  AddShader(faceProgram_, FaceVertShader, FaceFragShader);
  AddShader(faceWithTextureProgram_, FaceWithTextureVertShader,
            FaceWithTextureFragShader);
  AddShader(skyBoxProgram_, SkyBoxVertShader, SkyBoxFragShader);
  AddShader(vertexProgram_, VertexVertShader, VertexGeomShader,
            VertexFragShader);

  // AddShader(edgeProgram_, EDGE_VERT_SHADER, EDGE_GEOM_SHADER,
  // EDGE_FRAG_SHADER); AddShader(dottedEdgesProgram_, EDGES_DOTTED_VERT_SHADER,
  //           EDGES_DOTTED_FRAG_SHADER);
  // AddShader(faceProgram_, FACE_VERT_SHADER, FACE_FRAG_SHADER);
  // AddShader(faceWithTextureProgram_, FACE_WITH_TEXTURE_VERT_SHADER,
  //           FACE_WITH_TEXTURE_FRAG_SHADER);
  // AddShader(skyBoxProgram_, SKY_BOX_VERT_SHADER, SKY_BOX_FRAG_SHADER);
  // AddShader(vertexProgram_, VERTEX_VERT_SHADER, VERTEX_GEOM_SHADER,
  //           VERTEX_FRAG_SHADER);
}

void ShaderDrawer::setAttributesWithoutTexture(ShaderProgram &program) {
  int vertLoc = program.attributeLocation("position");
  program.enableAttributeArray(vertLoc);
  program.setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(dto::Point3D));
}
void ShaderDrawer::setMVP(ShaderProgram &program, Object &obj) {
  program.setUniformValue("model", obj.getModelMatrix()._matrix);
  program.setUniformValue("view", view_);
  program.setUniformValue("projection", projection_);
}

void ShaderDrawer::drawFaces(Object &obj) {
  obj.indexBuffer.bind();
  obj.vertexBuffer.bind();

  faceProgram_.bind();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  setMVP(faceProgram_, obj);
  setAttributesWithoutTexture(faceProgram_);
  faceProgram_.setUniformValue("PointColor", QVector4D(1.0f, 0.f, 0.f, 1.0f));

  glDrawElements(GL_TRIANGLES, obj.indexBuffer.size(), GL_UNSIGNED_INT, 0);

  faceProgram_.release();
  obj.vertexBuffer.release();
  obj.indexBuffer.release();
}
void ShaderDrawer::drawEdges(Object &obj) {
  obj.indexBuffer.bind();
  obj.vertexBuffer.bind();

  edgeProgram_.bind();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  setAttributesWithoutTexture(edgeProgram_);
  setMVP(edgeProgram_, obj);

  edgeProgram_.setUniformValue(
      "PointColor", color_from_settings(settings_.edgeSettings_.color));
  edgeProgram_.setUniformValue("ViewportInvSize", resolution_);
  edgeProgram_.setUniformValue("Thickness", settings_.edgeSettings_.pointSize);

  glDrawElements(GL_TRIANGLES, obj.indexBuffer.size(), GL_UNSIGNED_INT, 0);

  edgeProgram_.release();

  obj.vertexBuffer.release();
  obj.indexBuffer.release();
}
void ShaderDrawer::drawDottedEdges(Object &obj) {
  obj.indexBuffer.bind();
  obj.vertexBuffer.bind();

  dottedEdgesProgram_.bind();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  setAttributesWithoutTexture(dottedEdgesProgram_);
  setMVP(dottedEdgesProgram_, obj);

  dottedEdgesProgram_.setUniformValue(
      "PointColor", color_from_settings(settings_.edgeSettings_.color));
  dottedEdgesProgram_.setUniformValue("Resolution", resolution_);
  dottedEdgesProgram_.setUniformValue("DashSize", 5.f);
  dottedEdgesProgram_.setUniformValue("GapSize", 25.f);

  glDrawElements(GL_TRIANGLES, obj.indexBuffer.size(), GL_UNSIGNED_INT, 0);

  dottedEdgesProgram_.release();

  obj.vertexBuffer.release();
  obj.indexBuffer.release();
}
void ShaderDrawer::drawVertex(Object &obj) {
  obj.indexBuffer.bind();
  obj.vertexBuffer.bind();

  vertexProgram_.bind();

  glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

  setMVP(vertexProgram_, obj);
  setAttributesWithoutTexture(vertexProgram_);

  vertexProgram_.setUniformValue(
      "PointColor", color_from_settings(settings_.vertexSettings_.color));
  vertexProgram_.setUniformValue("PointSize",
                                 settings_.vertexSettings_.pointSize);
  vertexProgram_.setUniformValue(
      "RoundPoint",
      settings_.vertexSettings_.type == models::VertexDisplayType::CIRCLE);

  glDrawElements(GL_POINTS, obj.indexBuffer.size(), GL_UNSIGNED_INT, 0);

  vertexProgram_.release();
  obj.vertexBuffer.release();
  obj.indexBuffer.release();
}

ShaderDrawer::ShaderDrawer(QOpenGLContext *context) {
  // if(!(context->isValid()))
  // {
  //   qDebug() << "invalid context";
  // }
  // if (!context->create()) {
  //   qDebug() << "no context created";
  // }
  // initializeOpenGLFunctions();
  LoadShaders();
}

void ShaderDrawer::draw(models::TransformableObject &obj) {
  auto glObj = (Object &)obj;  // dynamic_cast?
  drawVertex(glObj);
  if (settings_.edgeSettings_.type == models::EdgeDisplayType::DOTTED) {
    drawDottedEdges(glObj);
  } else {
    drawEdges(glObj);
  }
  drawFaces(glObj);

  // glObj.getVertexBuffer().bind();
  // glObj.getIndexBuffer().bind();

  // if (glObj.getTexture().isCreated())
  // {
  //   glObj.getTexture().bind();
  //   glObj.getTextureCoordBuffer().bind();
  // }
}

// void ShaderDrawer::setAttributesWithoutTexture(ShaderProgram &program)
// {
//   int vertLoc = program.attributeLocation("position");
//   program.enableAttributeArray(vertLoc);
//   program.setAttributeArray(vertLoc, GL_FLOAT, 0, 3, sizeof(QVector3D));
// };

// void ShaderDrawer::setUniforms(ShaderProgram &program)
// {
// }
ShaderDrawer::~ShaderDrawer() {}

}  // namespace opengl
