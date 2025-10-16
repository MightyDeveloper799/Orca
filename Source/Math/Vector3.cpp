#include "Vector3.h"

namespace Orca
{
    Vector3::Vector3(float uniform) : x(uniform), y(uniform), z(uniform) { }
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    float Vector3::Length() const 
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 Vector3::Normalized() const
    {
        float len = Length();
        return len > 0 ? Vector3(x / len, y / len, z / len) : Vector3(0, 0, 0);
    }

    float Vector3::Dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::Cross(const Vector3& other) const 
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    Vector3 Vector3::operator+(const Vector3& other) const 
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator-(const Vector3& other) const 
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator*(float scalar) const 
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
}