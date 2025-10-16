#include "SquareCollider.h"

namespace Orca
{
	SquareCollider::SquareCollider(float width, float height, float depth)
	{
		m_BoxShape = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
	}

	btCollisionShape* SquareCollider::GetShape()
	{
		return m_BoxShape;
	}
}