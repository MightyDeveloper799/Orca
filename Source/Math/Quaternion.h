#pragma once

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include "Matrix4.h"
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    struct ORCA_API Quaternion 
    {
        float x, y, z, w;

        Quaternion();
        Quaternion(float x, float y, float z, float w);

        Quaternion Normalized() const;
        Vector3 operator*(const Vector3& v) const;
        Matrix4 ToMatrix() const;
    };
#pragma warning(pop)
}

#endif