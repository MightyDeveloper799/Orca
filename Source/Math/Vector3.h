#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include "../OrcaAPI.h"
#include <glm/glm.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    struct ORCA_API Vector3
    {
        float x, y, z;

        Vector3() = default;
        Vector3(float uniform);
        Vector3(float x, float y, float z);

        float Length() const;
        Vector3 Normalized() const;
        float Dot(const Vector3& other) const;
        Vector3 Cross(const Vector3& other) const;

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(float scalar) const;
    };
#pragma warning(pop)
}

#endif
