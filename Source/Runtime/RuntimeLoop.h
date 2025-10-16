#pragma once

#include "RuntimeContext.h"
#include "AnimationSystem.h"
#include "PhysicsSystem.h"
#include "ScriptSystem.h"
#include "RenderSystem.h"

namespace Orca 
{
    void RunFrame(RuntimeContext& ctx);
}