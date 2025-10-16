#pragma once

#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include "Component.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "../OrcaAPI.h"
#include <btBulletDynamicsCommon.h>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API RigidBodyComponent : public Component
	{
	public:
		RigidBodyComponent(btCollisionShape* shape, float mass);
		~RigidBodyComponent();

		void OnStart() override;
		void Update(float dt) override;

		void Simulate(float dt);

		void ApplyForce(const Vector3& force);
		void ApplyImpulse(const Vector3& impulse);

		Vector3 GetPosition() const;
		Quaternion GetRotation() const;
		Vector3 GetScale() const;

		void SetPosition(const Vector3& pos);
		void SetRotation(const Quaternion& rot);
		void SetScale(const Vector3& scale);

		btRigidBody* GetBody() const;

	private:
		btCollisionShape* collisionShape = nullptr;
		btRigidBody* rigidBody = nullptr;
		btDefaultMotionState* motionState = nullptr;
		float mass = 1.0f;
	};
#pragma warning(pop)
}

#endif