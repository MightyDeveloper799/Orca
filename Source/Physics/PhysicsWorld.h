#pragma once

#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <btBulletDynamicsCommon.h>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class PhysicsWorld 
    {
    public:
        PhysicsWorld();
        ~PhysicsWorld();

        void StepSimulation(float deltaTime);
        btDiscreteDynamicsWorld* GetWorld();

    private:
        btDefaultCollisionConfiguration* collisionConfig;
        btCollisionDispatcher* dispatcher;
        btBroadphaseInterface* broadphase;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;
    };
#pragma warning(pop)
}

#endif