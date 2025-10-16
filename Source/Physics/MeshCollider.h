#pragma once

#ifndef MESH_COLLIDER_H
#define MESH_COLLIDER_H

#include <btBulletDynamicsCommon.h>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class MeshCollider
	{
	public:
		MeshCollider(const btTriangleMesh* mesh);
		btCollisionShape* GetShape();

	public:
		btBvhTriangleMeshShape* m_CapsuleShape;
	};
#pragma warning(pop)
}

#endif