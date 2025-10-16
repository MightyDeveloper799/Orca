#include "MathUtils.h"

namespace Orca
{
    float MathUtils::Clamp(float value, float min, float max) 
    {
        return std::fmax(min, std::fmin(max, value));
    }

    float MathUtils::Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    float MathUtils::ToRadians(float degrees)
    {
        return degrees * (PI / 180.0f);
    }
}