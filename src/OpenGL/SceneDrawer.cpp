#include <Domain/Transform.h>
#include <OpenGL/SceneDrawer.h>
#include <OpenGL/SceneObject.h>

using namespace OpenGL;
using namespace Domain;

SceneDrawer::SceneDrawer(std::vector<ISceneDrawerPtr> &&drawers, CameraPtr camera, QWidget *pr)
    : QOpenGLWidget(pr), _drawers(drawers), _camera(camera)
{
    SetFPS(60);
}

void SceneDrawer::initializeGL()
{
    initializeOpenGLFunctions();

    for (auto &drawer : _drawers)
    {
        drawer->Initialize();
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_CUBE_MAP);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    static bool a = true;
    if (a)
    {
        const std::vector<uint32_t> cubeIndices = {// Front face
                                                   0, 1, 2, 0, 2, 3,
                                                   // Back face
                                                   4, 5, 6, 4, 6, 7,
                                                   // Left face
                                                   8, 9, 10, 8, 10, 11,
                                                   // Right face
                                                   12, 13, 14, 12, 14, 15,
                                                   // Top face
                                                   16, 17, 18, 16, 18, 19,
                                                   // Bottom face
                                                   20, 21, 22, 20, 22, 23};

        std::vector<Vertex> cubeVertices = {
            // Position            Texture Coords. Normals           Tangent        BiTangent
            // Front face
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            // Back face
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {-0.0f, -0.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-0.0f, -0.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {-0.0f, -0.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {-0.0f, -0.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            // Left face
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {1.f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            // Right face
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            // Top face
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            // Bottom face
            {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        };
        auto cube = std::make_shared<SceneObject>(cubeVertices, cubeIndices);
        _scene->AddModel(cube);
        a = false;
    }
}

void SceneDrawer::paintGL()
{

    auto color = _settings.GetFloorSettings().Color;
    glClearColor(color.x(), color.y(), color.z(), color.w());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &drawer : _drawers)
    {
        _scene->Draw(*drawer);
    }

    static Transform trans;
    trans.Rotate(0.001, 0, 0.001);
    _scene->ApplyTransform(trans);
}

void SceneDrawer::resizeGL(int w, int h)
{
    _settings.GetDisplaySettings().AspectRatio = (float)w / (float)h;
    _camera->Update();
    _settings.GetDisplaySettings().InvSizes = QVector2D(w, h);
}

ScenePtr SceneDrawer::Scene()
{
    return _scene;
}

void SceneDrawer::SetFPS(float fps)
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->start(1000 / fps);
}
