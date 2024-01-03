#include <Services/TransformBuilder.h>

#include <cmath>

namespace services {

dto::TransformMatrix TransformBuilder::buildRotateMatrix(dto::Point3D point) {
  dto::TransformMatrix rotateMatrix;

  // Извлечение углов поворота из входной точки
  float angleX = point.x;
  float angleY = point.y;
  float angleZ = point.z;

  // Вычисление синуса и косинуса для каждого угла
  float sinX = sin(angleX);
  float cosX = cos(angleX);
  float sinY = sin(angleY);
  float cosY = cos(angleY);
  float sinZ = sin(angleZ);
  float cosZ = cos(angleZ);

  // Построение матрицы поворота
  rotateMatrix._matrix[0][0] = cosY * cosZ;
  rotateMatrix._matrix[0][1] = cosY * sinZ;
  rotateMatrix._matrix[0][2] = -sinY;
  rotateMatrix._matrix[0][3] = 0.0f;

  rotateMatrix._matrix[1][0] = (sinX * sinY * cosZ) - (cosX * sinZ);
  rotateMatrix._matrix[1][1] = (sinX * sinY * sinZ) + (cosX * cosZ);
  rotateMatrix._matrix[1][2] = sinX * cosY;
  rotateMatrix._matrix[1][3] = 0.0f;

  rotateMatrix._matrix[2][0] = (cosX * sinY * cosZ) + (sinX * sinZ);
  rotateMatrix._matrix[2][1] = (cosX * sinY * sinZ) - (sinX * cosZ);
  rotateMatrix._matrix[2][2] = cosX * cosY;
  rotateMatrix._matrix[2][3] = 0.0f;

  rotateMatrix._matrix[3][0] = 0.0f;
  rotateMatrix._matrix[3][1] = 0.0f;
  rotateMatrix._matrix[3][2] = 0.0f;
  rotateMatrix._matrix[3][3] = 1.0f;

  return rotateMatrix;
}

dto::TransformMatrix TransformBuilder::buildScaleMatrix(dto::Point3D point) {
  dto::TransformMatrix scaleMatrix;

  // Extract scaling factors from the input point
  float scaleX = point.x;
  float scaleY = point.y;
  float scaleZ = point.z;

  // Build the scale matrix
  scaleMatrix._matrix[0][0] = scaleX;
  scaleMatrix._matrix[0][1] = 0.0f;
  scaleMatrix._matrix[0][2] = 0.0f;
  scaleMatrix._matrix[0][3] = 0.0f;

  scaleMatrix._matrix[1][0] = 0.0f;
  scaleMatrix._matrix[1][1] = scaleY;
  scaleMatrix._matrix[1][2] = 0.0f;
  scaleMatrix._matrix[1][3] = 0.0f;

  scaleMatrix._matrix[2][0] = 0.0f;
  scaleMatrix._matrix[2][1] = 0.0f;
  scaleMatrix._matrix[2][2] = scaleZ;
  scaleMatrix._matrix[2][3] = 0.0f;

  scaleMatrix._matrix[3][0] = 0.0f;
  scaleMatrix._matrix[3][1] = 0.0f;
  scaleMatrix._matrix[3][2] = 0.0f;
  scaleMatrix._matrix[3][3] = 1.0f;

  return scaleMatrix;
}

dto::TransformMatrix TransformBuilder::buildMoveMatrix(dto::Point3D point) {
  dto::TransformMatrix moveMatrix;

  // Extract translation values from the input point
  float translateX = point.x;
  float translateY = point.y;
  float translateZ = point.z;

  // Build the translation matrix
  moveMatrix._matrix[0][0] = 1.0f;
  moveMatrix._matrix[0][1] = 0.0f;
  moveMatrix._matrix[0][2] = 0.0f;
  moveMatrix._matrix[0][3] = translateX;

  moveMatrix._matrix[1][0] = 0.0f;
  moveMatrix._matrix[1][1] = 1.0f;
  moveMatrix._matrix[1][2] = 0.0f;
  moveMatrix._matrix[1][3] = translateY;

  moveMatrix._matrix[2][0] = 0.0f;
  moveMatrix._matrix[2][1] = 0.0f;
  moveMatrix._matrix[2][2] = 1.0f;
  moveMatrix._matrix[2][3] = translateZ;

  moveMatrix._matrix[3][0] = 0.0f;
  moveMatrix._matrix[3][1] = 0.0f;
  moveMatrix._matrix[3][2] = 0.0f;
  moveMatrix._matrix[3][3] = 1.0f;

  return moveMatrix;
}

}  // namespace services