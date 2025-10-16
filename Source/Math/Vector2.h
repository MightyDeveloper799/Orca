#pragma once

#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	struct ORCA_API Vector2
	{
		float x, y;

        Vector2();
        Vector2(float x, float y);

        float Length() const;
        Vector2 Normalized() const;
        float Dot(const Vector2& other) const;

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(float scalar) const;
	};
#pragma warning(pop)
}

#endif