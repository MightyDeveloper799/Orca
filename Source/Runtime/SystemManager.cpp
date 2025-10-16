#include "SystemManager.h"
#include "ScriptSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

namespace Orca 
{
    void SystemManager::Initialize(RuntimeContext& r_Ctx) 
    {
        ScriptSystem::Initialize(r_Ctx);
        PhysicsSystem::Initialize();
        RenderSystem::Initialize();
    }

    void SystemManager::Update(RuntimeContext& ctx) 
    {
        ScriptSystem::Execute(ctx);
        PhysicsSystem::Update(ctx);
    }

    void SystemManager::Render(RuntimeContext& ctx) 
    {
        RenderSystem::Render(ctx);
    }

    void SystemManager::Shutdown() 
    {
        RenderSystem::Shutdown();
        PhysicsSystem::Shutdown();
        ScriptSystem::Shutdown();
    }

}