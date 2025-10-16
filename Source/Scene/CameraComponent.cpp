#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "../Math/MathUtils.h"

namespace Orca
{
	CameraComponent::CameraComponent(float fov, float aspect, float nearPlane, float farPlane)
		:fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane)
	{
		UpdateProjectionMatrix();
	}

	void CameraComponent::OnStart()
	{
		UpdateViewMatrix();
	}

	void CameraComponent::Update(float dt)
	{
		if (!active) return;
		UpdateViewMatrix();
	}

	void CameraComponent::UpdateViewMatrix()
	{
		auto* transform = owner ? owner->GetComponent<TransformComponent>() : nullptr;
		if (!transform) return;

		Vector3 position = transform->GetPosition();
		Quaternion rotation = transform->GetRotation();

		Vector3 forward = rotation * Vector3(0, 0, -1);
		Vector3 up = rotation * Vector3(0, 1, 0);

		viewMatrix = Matrix4::LookAt(position, position + forward, up);
	}

	void CameraComponent::UpdateProjectionMatrix()
	{
		projectionMatrix = Matrix4::Perspective(MathUtils::ToRadians(fov), aspect, nearPlane, farPlane);
	}

	const Matrix4& CameraComponent::GetViewMatrix() const
	{
		return viewMatrix;
	}

	const Matrix4& CameraComponent::GetProjectionMatrix() const
	{
		return projectionMatrix;
	}

	float CameraComponent::GetFOV() const
	{
		return fov;
	}

	void CameraComponent::SetFOV(float fov)
	{
		this->fov = fov;
		this->UpdateProjectionMatrix();
	}

	float CameraComponent::GetAspect() const
	{
		return aspect;
	}

	void CameraComponent::SetAspect(float aspect)
	{
		this->aspect = aspect;
		this->GetProjectionMatrix();
	}

	float CameraComponent::GetNearPlane() const
	{
		return nearPlane;
	}

	void CameraComponent::SetNearPlane(float nearPlane)
	{
		this->nearPlane = nearPlane;
		this->GetProjectionMatrix();
	}

	float CameraComponent::GetFarPlane() const
	{
		return farPlane;
	}

	void CameraComponent::SetFarPlane(float farPlane)
	{
		this->farPlane = farPlane;
		this->GetProjectionMatrix();
	}

	void CameraComponent::SetActive(bool active)
	{
		this->active = active;
	}

	bool CameraComponent::IsActive() const
	{
		return active;
	}
}