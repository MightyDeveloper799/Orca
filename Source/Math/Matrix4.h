#pragma once

#ifndef MATRIX4_H
#define MATRIX4_H

#include <array>
#include <glm/glm.hpp>
#include "Vector3.h"
#include "../OrcaAPI.h"
#include <glm/gtc/type_ptr.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    struct ORCA_API Matrix4 
    {
        std::array<float, 16> m;

        static Matrix4 Identity();
        static Matrix4 Translation(const Vector3& t);
        static Matrix4 Scale(const Vector3& s);
        static Matrix4 RotationX(float angle);
        static Matrix4 RotationY(float angle);
        static Matrix4 RotationZ(float angle);
        static Matrix4 Perspective(float fov, float aspect, float near, float far);
        static Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

        Matrix4 operator*(const Matrix4& other) const;
        operator glm::mat4() const
        {
            return glm::make_mat4(m.data());
        }
    };
#pragma warning(pop)
}

#endif