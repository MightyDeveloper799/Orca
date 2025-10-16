#pragma once

#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <cmath>

namespace Orca 
{
    namespace MathUtils
    {
        constexpr float PI = 3.14159265359f;
        constexpr float EPSILON = 1e-5f;

        float Clamp(float value, float min, float max);
        float Lerp(float a, float b, float t);
        float ToRadians(float degrees);
    }
}

#endif