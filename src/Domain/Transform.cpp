#include <Domain/Transform.h>

using namespace Domain;

Transform::Transform()
{
    _transform.setToIdentity();
}

void Transform::Rotate(float xDegree, float yDegree, float zDegree)
{
    _transform.rotate(xDegree, 1, 0, 0);
    _transform.rotate(yDegree, 0, 1, 0);
    _transform.rotate(zDegree, 0, 0, 1);
}

void Transform::Translate(float dx, float dy, float dz)
{
    _transform.translate(dx, dy, dz);
}

void Transform::Apply(QMatrix4x4 &model)
{
    model = model * _transform;
}
