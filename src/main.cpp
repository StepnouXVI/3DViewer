#include <QApplication>
#include <Core/SceneDrawer.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SceneDrawer sceneDrawer;

    sceneDrawer.show();

    return a.exec();
}


