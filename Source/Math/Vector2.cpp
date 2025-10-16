#include "Vector2.h"

namespace Orca
{
    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    float Vector2::Length() const 
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Vector2::Normalized() const 
    {
        float len = Length();
        return len > 0 ? Vector2(x / len, y / len) : Vector2(0, 0);
    }
    float Vector2::Dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const 
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(float scalar) const 
    {
        return Vector2(x * scalar, y * scalar);
    }
}