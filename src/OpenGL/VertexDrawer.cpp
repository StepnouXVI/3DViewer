#include <Consts/ShaderPaths.h>
#include <Domain/Vertex.h>
#include <OpenGL/VertexDrawer.h>

using namespace Domain;
using namespace OpenGL;

VertexDrawer::VertexDrawer(CameraPtr camera) : _camera(camera)
{
}

void VertexDrawer::Draw(ISceneObject &obj)
{
    static float a = 0;
    if (_settings.GetVertexSettings().Type == VertexDisplayType::NONE)
        return;
    _program.bind();

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glEnable(GL_PROGRAM_POINT_SIZE);

    SetUpData(_program, obj);
    SetMVP(_program, *_camera, obj);

    _program.setUniformValue("PointColor", _settings.GetVertexSettings().Color);
    _program.setUniformValue("RoundPoint", _settings.GetVertexSettings().Type == VertexDisplayType::CIRCLE);
    _program.setUniformValue("PointSize", _settings.GetVertexSettings().PointSize + a);

    glDrawElements(GL_TRIANGLES, obj.EdgeCount(), GL_UNSIGNED_INT, nullptr);

    UnSetData(_program, obj);
    _program.release();
}

void VertexDrawer::Initialize()
{
    AddShaders(_program, VERTEX_VERT_SHADER, VERTEX_FRAG_SHADER);
}
