#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "../Runtime/RuntimeContext.h"
#include "Window.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class Engine 
    {
    public:
        Engine();
        ~Engine();

        void Initialize(RuntimeContext& ctx);
        void Update(RuntimeContext& ctx);
        void Render(RuntimeContext& ctx);
        void Shutdown();

        Window* GetWindow() const;
        void SetWindow(Window* window);

        bool IsRunning() const;
        float GetDeltaTime() const;

    private:
        bool m_Running = true;
        float m_LastFrameTime = 0.0f;
        float m_DeltaTime = 0.0f;
        Window* window = nullptr;
    };
}

#endif