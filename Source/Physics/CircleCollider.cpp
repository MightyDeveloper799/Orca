#include "CircleCollider.h"

namespace Orca
{
	CircleCollider::CircleCollider(float radius)
	{
		m_SphereShape = new btSphereShape(radius);
	}

	btCollisionShape* CircleCollider::GetShape()
	{
		return m_SphereShape;
	}
}