#include <QApplication>
#include <Core/SceneDrawer.h>
#include <QFile>
#include <iostream>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    CustomQOpenGLWidget sceneDrawer;

    sceneDrawer.show();

    return a.exec();
}


