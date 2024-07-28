#include <Domain/Camera.h>


namespace Domain
{
    Camera::Camera()
    {
        SetProjection();
        SetView();
    }

    void Camera::SetProjection()
    {
        float aspectRatio = _settings.GetDisplaySettings().AspectRatio;
    _projection.setToIdentity();

    if (_settings.GetDisplaySettings().ProjectionType == ProjectionType::PARALLEL)
        _projection.ortho(-aspectRatio, aspectRatio, -1.0, 1.0, 0.01f, 500.0f);
    else
        _projection.perspective(aspectRatio, aspectRatio, 0.01f, 500.0f);
    }

    void Camera::SetView()
    {
        _view.setToIdentity();
        
        _view.lookAt(_position, _position + _lookAt, _up);
    }

    QMatrix4x4 Camera::Projection() const
    {
        return _projection;
    }

    QMatrix4x4 Camera::View() const{
        return _view;
    }

    void Camera::Move(QVector3D delta)
    {
        _position = _position + delta;
    }

    void Camera::Rotate(float xDegree, float yDegree, float zDegree)
    {
        QMatrix4x4 r;
        r.setToIdentity();
        r.rotate(xDegree, 1, 0, 0);
        r.rotate(yDegree, 0, 1, 0);
        r.rotate(zDegree, 0, 0, 1);

        _lookAt = r.mapVector(_lookAt);
    }

    void Camera::Update()
    {
        SetProjection();
        SetView();
    }
}