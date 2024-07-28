#include <Domain/Vertex.h>
#include <OpenGL/SceneDrawer.h>
#include <OpenGL/SceneObject.h>
#include <OpenGL/VertexDrawer.h>
#include <OpenGL/EdgeDrawer.h>
#include <QApplication>
#include <memory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Domain::SceneSettings::GetInstance().GetVertexSettings().Type = Domain::VertexDisplayType::CIRCLE;
    Domain::SceneSettings::GetInstance().GetVertexSettings().Color = QVector4D(1,1,1,1);
    Domain::SceneSettings::GetInstance().GetVertexSettings().PointSize = 10;
    Domain::CameraPtr camera = std::make_shared<Domain::Camera>();
    auto vertDrawer = std::make_shared<OpenGL::VertexDrawer>(camera);
    auto edgeDrawer = std::make_shared<OpenGL::EdgeDrawer>(camera);

    std::vector<Domain::ISceneDrawerPtr> drawers = {vertDrawer, edgeDrawer};

    OpenGL::SceneDrawer sDrawer(std::move(drawers), camera);




    sDrawer.show();

    return a.exec();
}
