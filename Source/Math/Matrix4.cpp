#include "Matrix4.h"
#include <cmath>
#include "MathUtils.h"

namespace Orca
{
	Matrix4 Matrix4::Identity()
	{
		Matrix4 mat = {};
		mat.m[0] = mat.m[5] = mat.m[10] = mat.m[15] = 1.0f;
		return mat;
	}

	Matrix4 Matrix4::Translation(const Vector3& t)
	{
		Matrix4 mat = Identity();
		mat.m[12] = t.x;
		mat.m[13] = t.y;
		mat.m[14] = t.z;
		return mat;
	}

	Matrix4 Matrix4::Scale(const Vector3& s)
	{
		Matrix4 mat = {};
		mat.m[0] = s.x;
		mat.m[5] = s.y;
		mat.m[10] = s.z;
		mat.m[15] = 1.0f;
		return mat;
	}

	Matrix4 Matrix4::RotationX(float angle)
	{
		Matrix4 mat = Identity();
		float c = std::cos(angle);
		float s = std::sin(angle);
		mat.m[5] = c;
		mat.m[6] = s;
		mat.m[9] = -s;
		mat.m[10] = c;
		return mat;
	}

	Matrix4 Matrix4::RotationY(float angle)
	{
		Matrix4 mat = Identity();
		float c = std::cos(angle);
		float s = std::sin(angle);
		mat.m[0] = c;
		mat.m[2] = -s;
		mat.m[8] = s;
		mat.m[10] = c;
		return mat;
	}

	Matrix4 Matrix4::RotationZ(float angle)
	{
		Matrix4 mat = Identity();
		float c = std::cos(angle);
		float s = std::sin(angle);
		mat.m[0] = c;
		mat.m[1] = s;
		mat.m[4] = -s;
		mat.m[5] = c;
		return mat;
	}

	Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far)
	{
		Matrix4 mat = {};
		float tanHalfFov = std::tan(fov / 2.0f);
		mat.m[0] = 1.0f / (aspect * tanHalfFov);
		mat.m[5] = 1.0f / tanHalfFov;
		mat.m[10] = -(far + near) / (far - near);
		mat.m[11] = -1.0f;
		mat.m[14] = -(2.0f * far * near) / (far - near);
		return mat;
	}

	Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 f = (target - eye).Normalized();
		Vector3 s = f.Cross(up).Normalized();
		Vector3 u = s.Cross(f);

		Matrix4 mat = Identity();
		mat.m[0] = s.x;
		mat.m[1] = u.x;
		mat.m[2] = -f.x;

		mat.m[4] = s.y;
		mat.m[5] = u.y;
		mat.m[6] = -f.y;

		mat.m[8] = s.z;
		mat.m[9] = u.z;
		mat.m[10] = -f.z;

		mat.m[12] = -s.Dot(eye);
		mat.m[13] = -u.Dot(eye);
		mat.m[14] = f.Dot(eye); // Note: some engines use -f.dot(eye)

		return mat;
	}

	Matrix4 Matrix4::operator*(const Matrix4& other) const
	{
		Matrix4 result = {};
		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				result.m[col + row * 4] =
					m[0 + row * 4] * other.m[col + 0] +
					m[1 + row * 4] * other.m[col + 4] +
					m[2 + row * 4] * other.m[col + 8] +
					m[3 + row * 4] * other.m[col + 12];
			}
		}
		return result;
	}
}