#pragma once
#include <QMatrix4x4>

namespace Domain
{
class Transform
{
    private:
        QMatrix4x4 _transform = QMatrix4x4();

    public:
        Transform();
        void Rotate(float xDegree, float yDegree, float zDegree);
        void Translate(float dx, float dy, float dz);
        void Apply(QMatrix4x4& model);

};
} // namespace Domain
