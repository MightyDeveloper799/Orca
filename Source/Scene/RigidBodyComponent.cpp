#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "../Physics/Physics.h"
#include "../Math/MathUtils.h"

namespace Orca
{
	RigidBodyComponent::RigidBodyComponent(btCollisionShape* shape, float mass)
		: collisionShape(shape), mass(mass)
	{
		btVector3 localInertia(0, 0, 0);
		if (mass > 0.0f)
			shape->calculateLocalInertia(mass, localInertia);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(0, 0, 0));

		motionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
		rigidBody = new btRigidBody(rbInfo);
	}

	RigidBodyComponent::~RigidBodyComponent()
	{
		if (rigidBody)
		{
			auto* world = Physics::GetWorld()->GetWorld();
			world->removeRigidBody(rigidBody);
			delete rigidBody;
		}

		delete motionState;
		delete collisionShape;
	}

	void RigidBodyComponent::OnStart()
	{
		auto* transformComp = owner->GetComponent<TransformComponent>();

		if (transformComp)
		{
			const Vector3& pos = transformComp->GetPosition();
			const Quaternion& rot = transformComp->GetRotation();

			btTransform btTrans;
			btTrans.setIdentity();
			btTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));
			btTrans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

			rigidBody->setWorldTransform(btTrans);
			motionState->setWorldTransform(btTrans);
		}

		Physics::GetWorld()->GetWorld()->addRigidBody(rigidBody);
	}

	void RigidBodyComponent::Update(float dt)
	{
		btTransform btTrans;
		rigidBody->getMotionState()->getWorldTransform(btTrans);
		btVector3 pos = btTrans.getOrigin();
		btQuaternion rot = btTrans.getRotation();

		auto* transformComp = owner->GetComponent<TransformComponent>();
		if (transformComp)
		{
			transformComp->SetPosition(Vector3(pos.x(), pos.y(), pos.z()));
			transformComp->SetRotation(Quaternion(rot.getX(), rot.getY(), rot.getZ(), rot.getW()));
		}
	}

	void RigidBodyComponent::Simulate(float dt)
	{
		if (!rigidBody || !owner) return;

		Physics::GetWorld()->GetWorld()->stepSimulation(dt);

		btTransform btTrans;
		rigidBody->getMotionState()->getWorldTransform(btTrans);
		btVector3 pos = btTrans.getOrigin();

		auto* transformComp = owner->GetComponent<TransformComponent>();

		if (transformComp)
		{
			transformComp->SetPosition(Vector3(pos.x(), pos.y(), pos.z()));
			btQuaternion rot = btTrans.getRotation();
			transformComp->SetRotation(Quaternion());
		}
	}

	void RigidBodyComponent::ApplyForce(const Vector3& force)
	{
		if (rigidBody)
			rigidBody->applyCentralImpulse(btVector3(force.x, force.y, force.z));
	}

	void RigidBodyComponent::ApplyImpulse(const Vector3& impulse)
	{
		if(rigidBody)
			rigidBody->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
	}

	Vector3 RigidBodyComponent::GetPosition() const
	{
		if (!rigidBody || !rigidBody->getMotionState()) return Vector3();

		btTransform btTrans;
		rigidBody->getMotionState()->getWorldTransform(btTrans);
		btVector3 pos = btTrans.getOrigin();
		return Vector3(pos.getX(), pos.getY(), pos.getZ());
	}

	Quaternion RigidBodyComponent::GetRotation() const
	{
		if (!rigidBody || !rigidBody->getMotionState()) return Quaternion();

		btTransform btTrans;
		rigidBody->getMotionState()->getWorldTransform(btTrans);
		btQuaternion rot = btTrans.getRotation();
		return Quaternion(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
	}

	Vector3 RigidBodyComponent::GetScale() const
	{
		auto* transformComp = owner ? owner->GetComponent<TransformComponent>() : nullptr;
		return transformComp ? transformComp->GetScale() : Vector3(1.0f);
	}

	btRigidBody* RigidBodyComponent::GetBody() const
	{
		return rigidBody;
	}
}