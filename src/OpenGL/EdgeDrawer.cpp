#include <Consts/ShaderPaths.h>
#include <Domain/Vertex.h>
#include <OpenGL/EdgeDrawer.h>

using namespace Domain;
using namespace OpenGL;

EdgeDrawer::EdgeDrawer(CameraPtr camera) : _camera(camera)
{
}

void EdgeDrawer::Draw(ISceneObject &obj)
{
    static float a = 0;

    _program.bind();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_PROGRAM_POINT_SIZE);

    SetUpData(_program, obj);
    SetMVP(_program, *_camera, obj);

    _program.setUniformValue("u_viewportInvSize", _settings.GetDisplaySettings().InvSizes);
    _program.setUniformValue("u_thickness", _settings.GetEdgeSettings().PointSize + a);
    _program.setUniformValue("PointColor", _settings.GetEdgeSettings().Color);

    glDrawElements(GL_TRIANGLES, obj.EdgeCount(), GL_UNSIGNED_INT, nullptr);

    UnSetData(_program, obj);
    _program.release();
}

void EdgeDrawer::Initialize()
{
    AddShaders(_program, EDGE_VERT_SHADER, EDGE_GEOM_SHADER, EDGE_FRAG_SHADER);
}
