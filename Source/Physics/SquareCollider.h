#pragma once

#ifndef SQUARE_COLLIDER_H
#define SQUARE_COLLIDER_H

#include <btBulletDynamicsCommon.h>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class SquareCollider
	{
	public:
		SquareCollider(float width, float height, float depth);
		btCollisionShape* GetShape();

	private:
		btBoxShape* m_BoxShape;
	};
#pragma warning(pop)
}

#endif