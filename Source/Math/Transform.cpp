#include "Transform.h"
#include "Matrix4.h"

namespace Orca
{
    Transform::Transform() : position(0, 0, 0), rotation(), scale(1, 1, 1) {}

    Matrix4 Transform::ToMatrix() const 
    {
        return Matrix4::Identity();
    }
}