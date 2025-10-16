#include "CapsuleCollider.h"

namespace Orca
{
    CapsuleCollider::CapsuleCollider(float radius, float height) 
    {
        m_CapsuleShape = new btCapsuleShape(radius, height);
    }

    btCollisionShape* CapsuleCollider::GetShape() 
    {
        return m_CapsuleShape;
    }
}