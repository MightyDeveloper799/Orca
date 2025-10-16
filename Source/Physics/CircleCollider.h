#pragma once

#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include <btBulletDynamicsCommon.h>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class CircleCollider
	{
	public:
		CircleCollider(float radius);
		btCollisionShape* GetShape();

	private:
		btSphereShape* m_SphereShape;
	};
#pragma warning(pop)
}

#endif