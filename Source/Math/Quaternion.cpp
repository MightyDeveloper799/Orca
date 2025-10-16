#include "Quaternion.h"
#include <cmath>

namespace Orca
{
    Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}
    Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Quaternion Quaternion::Normalized() const {
        float len = std::sqrt(x * x + y * y + z * z + w * w);
        return Quaternion(x / len, y / len, z / len, w / len);
    }

    Matrix4 Quaternion::ToMatrix() const
    {
        Matrix4 mat;
        float xx = x * x;
        float yy = y * y;
        float zz = z * z;
        float xy = x * y;
        float xz = x * z;
        float yz = y * z;
        float wx = w * x;
        float wy = w * y;
        float wz = w * z;

        mat.m[0] = 1.0f - 2.0f * (yy + zz);
        mat.m[1] = 2.0f * (xy + wz);
        mat.m[2] = 2.0f * (xz - wy);
        mat.m[3] = 0.0f;

        mat.m[4] = 2.0f * (xy - wz);
        mat.m[5] = 1.0f - 2.0f * (xx + zz);
        mat.m[6] = 2.0f * (yz + wx);
        mat.m[7] = 0.0f;

        mat.m[8] = 2.0f * (xz + wy);
        mat.m[9] = 2.0f * (yz - wx);
        mat.m[10] = 1.0f - 2.0f * (xx + yy);
        mat.m[11] = 0.0f;

        mat.m[12] = mat.m[13] = mat.m[14] = 0.0f;
        mat.m[15] = 1.0f;
        
        return mat;
    }

    Vector3 Quaternion::operator*(const Vector3& v) const
    {
        Vector3 qVec(x, y, z);
        Vector3 t = qVec.Cross(v) * 2.0f;
        Vector3 result = v + t * w + qVec.Cross(t);
        return result;
    }
}