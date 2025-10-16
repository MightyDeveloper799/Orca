#include "PhysicsSystem.h"
#include "../Scene/RigidbodyComponent.h"
#include "../Scene/Entity.h"
#include "../Scene/Scene.h"

namespace Orca {

    void PhysicsSystem::Initialize() 
    {
        // Initialize physics world, gravity, collision layers, etc.
    }

    void PhysicsSystem::Update(RuntimeContext& ctx) 
    {
        std::shared_ptr<Scene> scene = ctx.GetActiveSceneShared();
        for (auto& entity : scene->GetEntitiesWith<RigidBodyComponent>()) 
        {
            RigidBodyComponent* rigidbody = entity->GetComponent<RigidBodyComponent>();
            if (rigidbody)
                rigidbody->Simulate(ctx.GetDeltaTime());
        }
    }

    void PhysicsSystem::Shutdown()
    {
        // Clean up physics world, free memory
    }
}