#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class Camera
	{
	public:
		Camera(float fov, float aspect, float nearPlane, float farPlane);

		void SetPos(const glm::vec3& pos);
		void SetRot(const glm::vec3& rot);

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;

		const glm::vec3& GetPos() const;
		const glm::vec3& GetRot() const;

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

		float m_FOV;
		float m_Aspect;
		float m_Near;
		float m_Far;
	};
#pragma warning(pop)
}

#endif