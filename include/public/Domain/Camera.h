#pragma once

#include <Domain/ITransformableObject.h>
#include <Domain/Settings.h>
#include <QMatrix4x4>
#include <memory>


namespace Domain
{
/**
 * @brief The Camera class
 *
 * Camera class describes a camera in 3d space.
 * It can be moved and rotated.
 */
class Camera
{
    /**
     * @brief _up
     *
     * up vector of camera
     */
  private:
    QVector3D _up = QVector3D(0, 0, 1);

    /**
     * @brief _position
     *
     * position of camera
     */
  private:
    QVector3D _position = QVector3D(50, 50, 50);

    /**
     * @brief _lookAt
     *
     * look at vector of camera
     */
  private:
    QVector3D _lookAt = QVector3D(-1, -1, -1);

    /**
     * @brief _projection
     *
     * projection matrix of camera
     */
  private:
    QMatrix4x4 _projection = QMatrix4x4();

    /**
     * @brief _view
     *
     * view matrix of camera
     */
  private:
    QMatrix4x4 _view = QMatrix4x4();

    /**
     * @brief _settings
     *
     * settings of scene
     */
  private:
    SceneSettings &_settings = SceneSettings::GetInstance();

  public:
    /**
     * @brief Camera
     *
     * Default constructor
     */
    Camera();

    QMatrix4x4 Projection() const;

    QMatrix4x4 View() const;

    /**
     * @brief Update
     *
     * updates the camera
     */
    void Update();

    /**
     * @brief Move
     *
     * @param pos
     *
     * moves the camera to the position
     */
    void Move(QVector3D pos);

    /**
     * @brief Rotate
     *
     * @param xDegree
     * @param yDegree
     * @param zDegree
     *
     * rotates the camera by the angles
     */
    void Rotate(float xDegree, float yDegree, float zDegree);

  private:
    /**
     * @brief SetProjection
     *
     * sets the projection matrix
     */
    void SetProjection();

    /**
     * @brief SetView
     *
     * sets the view matrix
     */
    void SetView();
};

using CameraPtr = std::shared_ptr<Camera>;

} // namespace Domain
