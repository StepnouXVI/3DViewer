#include <Consts/ShaderPaths.h>
#include <Domain/Vertex.h>
#include <OpenGL/FloorDrawer.h>

using namespace Domain;
using namespace OpenGL;

FloorDrawer::FloorDrawer(CameraPtr camera) : _camera(camera)
{
}

void FloorDrawer::Draw(ISceneObject &obj)
{
    static float a = 0;

    _program.bind();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_PROGRAM_POINT_SIZE);

    SetMVP(_program, *_camera, obj);

    _program.setUniformValue("u_viewportInvSize", _settings.GetDisplaySettings().InvSizes);
    _program.setUniformValue("u_thickness", _settings.GetFloorSettings().PointSize + a);
    _program.setUniformValue("PointColor", _settings.GetFloorSettings().Color);

    glDrawElements(GL_TRIANGLES, obj.EdgeCount(), GL_UNSIGNED_INT, nullptr);

    UnSetData(_program, obj);
    _program.release();
}

void FloorDrawer::Initialize()
{
    AddShaders(_program, FLOOR_VERT_SHADER, FLOOR_FRAG_SHADER);
}
