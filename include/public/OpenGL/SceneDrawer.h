#pragma once
#include <Domain/ISceneDrawer.h>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <vector> 
#include <Domain/Settings.h>
#include <Domain/Scene.h>
#include <Domain/Camera.h>

namespace OpenGL
{
    class SceneDrawer : public QOpenGLWidget, protected QOpenGLFunctions
    {
        Q_OBJECT
        private:
            std::vector<Domain::ISceneDrawerPtr> _drawers;
            Domain::SceneSettings& _settings = Domain::SceneSettings::GetInstance();
            Domain::ScenePtr _scene = std::make_shared<Domain::Scene>();
            Domain::CameraPtr _camera;
            QTimer* _timer;

                        
            
        public:
            SceneDrawer(std::vector<Domain::ISceneDrawerPtr>&& drawers, Domain::CameraPtr camera, QWidget* pr = nullptr);

            Domain::ScenePtr Scene();

            void initializeGL() override;
            void paintGL() override;
            void resizeGL(int w, int h) override;


        private:
            void SetFPS(float fps);

    };
}