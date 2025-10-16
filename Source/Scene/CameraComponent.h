#pragma once

#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "Component.h"
#include "../Math/Matrix4.h"
#include "../Math/Vector3.h"
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API CameraComponent : public Component
	{
	public:
		CameraComponent(float fov = 60.0f, float aspect = 1.777f, float nearPlane = 0.1f, float farPlane = 1000.0f);

		void OnStart() override;
		void Update(float dt) override;

		const Matrix4& GetViewMatrix() const;
		const Matrix4& GetProjectionMatrix() const;

		float GetFOV() const;
		void SetFOV(float fov);
		float GetAspect() const;
		void SetAspect(float aspect);
		float GetNearPlane() const;
		void SetNearPlane(float nearPlane);
		float GetFarPlane() const;
		void SetFarPlane(float farPlane);

		void SetActive(bool active);
		bool IsActive() const;

	private:
		Matrix4 viewMatrix, projectionMatrix;

		float fov, aspect, nearPlane, farPlane;

		bool active = true;

		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
	};
#pragma warning(pop)
}

#endif