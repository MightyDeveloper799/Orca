#pragma once

#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include "../Math/Transform.h"
#include "../OrcaAPI.h"
#include <glm/glm.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API TransformComponent : public Component
	{
	public:
		TransformComponent() = default;

		void Update(float deltaTime) override;
		void Render() override;

		Matrix4 GetMatrix() const;
		const Vector3& GetPosition() const;
		const Quaternion& GetRotation() const;
		const Vector3& GetScale() const;

		void SetPosition(const Vector3& pos);
		void SetRotation(const Quaternion& rot);
		void SetScale(const Vector3& scale);
	private:
		Transform transform;
	};
#pragma warning(pop)
}

#endif