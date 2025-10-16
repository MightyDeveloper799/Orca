#include "Physics.h"

namespace Orca
{
	PhysicsWorld* Physics::world = nullptr;

    void Physics::Initialize() {
        world = new PhysicsWorld();
    }

    void Physics::Update(float deltaTime) {
        if (world) world->StepSimulation(deltaTime);
    }

    PhysicsWorld* Physics::GetWorld() {
        return world;
    }
}