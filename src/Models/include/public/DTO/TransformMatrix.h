#pragma once

namespace dto {

class TransformMatrix {
 public:
  float _matrix[4][4];

 public:
  TransformMatrix();
  TransformMatrix operator*(const TransformMatrix &other) const;

  static TransformMatrix getIdentityMatrix();
};

}  // namespace dto
