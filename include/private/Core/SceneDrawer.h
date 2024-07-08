#pragma once

#include <QOpenGLWidget>
#include <QMatrix4x4>

#include <QOpenGLFunctions>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>


class SceneDrawer : public QOpenGLWidget
{
    Q_OBJECT

    private:
    QMatrix4x4 _view;
    QMatrix4x4 _projection; 
    protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    public:
    SceneDrawer(QWidget* parent = nullptr);
    ~SceneDrawer();
};
