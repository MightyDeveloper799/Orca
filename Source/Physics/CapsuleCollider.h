#pragma once

#ifndef CAPSULE_COLIDER_H
#define CAPSULE_COLLIDER_H

#include <btBulletDynamicsCommon.h>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class CapsuleCollider 
    {
    public:
        CapsuleCollider(float radius, float height);
        btCollisionShape* GetShape();

    private:
        btCapsuleShape* m_CapsuleShape;
    };
#pragma warning(pop)
}

#endif