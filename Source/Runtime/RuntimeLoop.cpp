#include "RuntimeLoop.h"

namespace Orca 
{
    static AnimationSystem animationSystem;
    static PhysicsSystem physicsSystem;
    static ScriptSystem scriptSystem;
    static RenderSystem renderSystem;

    void RunFrame(RuntimeContext& ctx) 
    {
        if (ctx.IsPaused()) return;

        animationSystem.Update(ctx);
        physicsSystem.Update(ctx);
        scriptSystem.Execute(ctx);
        renderSystem.Render(ctx);
    }
}