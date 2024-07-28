#pragma once

namespace Domain
{
    class Transform;
class ITransformableObject
{
    public:
    virtual void ApplyTransform(Transform&) = 0;
};

} // namespace Domain
