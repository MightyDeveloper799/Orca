#pragma once

#ifndef PHYSICS_H
#define PHYSICS_H

#include "PhysicsWorld.h"
#include <vector>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class Physics 
    {
    public:
        static void Initialize();
        static void Update(float deltaTime);
        static PhysicsWorld* GetWorld();

    private:
        static PhysicsWorld* world;
    };
#pragma warning(pop)
}

#endif