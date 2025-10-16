#pragma once

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "RuntimeContext.h"

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class SystemManager 
    {
    public:
        static void Initialize(RuntimeContext& r_Ctx);
        static void Update(RuntimeContext& ctx);
        static void Render(RuntimeContext& ctx);
        static void Shutdown();
    };
#pragma warning(pop)
}

#endif