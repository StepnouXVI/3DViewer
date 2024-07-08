#include <Core/SceneDrawer.h>


SceneDrawer::SceneDrawer(QWidget* parent) : QOpenGLWidget(parent)
{
}

void SceneDrawer::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void SceneDrawer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneDrawer::resizeGL(int w, int h)
{
    float aspect = static_cast<float>(w) / static_cast<float>(h);

    _projection.setToIdentity();
    _projection.perspective(90.0f, aspect, 0.1f, 100.0f);
}

SceneDrawer::~SceneDrawer()
{
}
