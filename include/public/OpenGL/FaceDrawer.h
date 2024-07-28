#pragma once
#include <Domain/ISceneDrawer.h>
#include <QOpenGLShaderProgram>
#include <Domain/Settings.h>
#include <Domain/Camera.h>
#include <OpenGL/SceneDrawerHelper.h>

namespace OpenGL
{
    class FaceDrawer : public Domain::ISceneDrawer, protected SceneDrawerHelper
    {
        private:
            Domain::SceneSettings& _settings = Domain::SceneSettings::GetInstance();
            QOpenGLShaderProgram _program;
            Domain::CameraPtr _camera;

        public:
            FaceDrawer(Domain::CameraPtr camera);
            void Draw(Domain::ISceneObject &) override;
            void Initialize() override;
    };
}