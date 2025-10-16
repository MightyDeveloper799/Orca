#include "TransformComponent.h"
#include "Entity.h"
#include "../Math/MathUtils.h"
#include "RigidBodyComponent.h"

namespace Orca
{
	void TransformComponent::Update(float dt)
	{
		if (this->owner)
		{
			auto rb = this->owner->GetComponent<RigidBodyComponent>();
			if (rb)
			{
				this->transform.position = rb->GetPosition();
				this->transform.rotation = rb->GetRotation();
				this->transform.scale = rb->GetScale();
			}
		}
	}

	void TransformComponent::Render()
	{
#ifdef ORCA_EDITOR
		if (owner && owner->IsSelected())
		{
			DebugDraw::DrawSphere(Position, 0.1f, Color::Yellow);

			Matrix4 model = GetMatrix();
			DebugDraw::DrawAxes(model, 0.5f);

			DebugDraw::DrawBox(model, Vector3(1.0f), Color::Cyan);
		}
#endif
	}


	Matrix4 TransformComponent::GetMatrix() const
	{
		Matrix4 translation = Matrix4::Translation(this->transform.position);
		Matrix4 rotation = this->transform.rotation.ToMatrix();
		Matrix4 scale = Matrix4::Scale(this->transform.scale);
		return translation * rotation * scale;
	}
	
	const Vector3& TransformComponent::GetPosition() const
	{
		return this->transform.position;
	}

	const Quaternion& TransformComponent::GetRotation() const
	{
		return this->transform.rotation;
	}

	const Vector3& TransformComponent::GetScale() const
	{
		return this->transform.scale;
	}

	void TransformComponent::SetPosition(const Vector3& pos)
	{
		this->transform.position = pos;
	}

	void TransformComponent::SetRotation(const Quaternion& rot)
	{
		this->transform.rotation = rot;
	}

	void TransformComponent::SetScale(const Vector3& scale)
	{
		this->transform.scale = scale;
	}
}