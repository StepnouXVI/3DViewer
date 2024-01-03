#include <DTO/TransformMatrix.h>

namespace dto {

TransformMatrix::TransformMatrix() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      _matrix[i][j] = 0;
    }
  }
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &other) const {
  TransformMatrix result;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
      }
    }
  }

  return result;
}

TransformMatrix TransformMatrix::getIdentityMatrix() {
  auto result = TransformMatrix();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (i == j) {
        result._matrix[i][j] = 1.0f;  // Главная диагональ - 1
      } else {
        result._matrix[i][j] = 0.0f;  // Остальные элементы - 0
      }
    }
  }
  return result;
}
}  // namespace dto