#include "MeshCollider.h"

namespace Orca
{
	MeshCollider::MeshCollider(const btTriangleMesh* mesh)
	{
		m_CapsuleShape = new btBvhTriangleMeshShape(const_cast<btTriangleMesh*>(mesh), true);
	}

	btCollisionShape* MeshCollider::GetShape()
	{
		return m_CapsuleShape;
	}
}