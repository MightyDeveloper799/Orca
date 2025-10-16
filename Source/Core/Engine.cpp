#include "Engine.h"
#include "Timer.h"
#include "Runtime/SystemManager.h"

namespace Orca 
{
    Engine::Engine() {}

    Engine::~Engine() = default;

    void Engine::Initialize(RuntimeContext& ctx) 
    {   
        SystemManager::Initialize(ctx);
        Timer timer;
        float t = timer.GetTime();
        m_LastFrameTime = t;
    }

    void Engine::Update(RuntimeContext& ctx) 
    {
        Timer timer;
        float currentTime = timer.GetTime();

        m_DeltaTime = currentTime - m_LastFrameTime;

        ctx.SetDeltaTime(m_DeltaTime);

        m_LastFrameTime = currentTime;

        SystemManager::Update(ctx);

        if (window)
        {
            window->OnUpdate();
        }
    }

    void Engine::Render(RuntimeContext& ctx) 
    {
        SystemManager::Render(ctx);
    }

    void Engine::Shutdown() 
    {
        SystemManager::Shutdown();

        window = nullptr;

        m_Running = false;
    }

    Window* Engine::GetWindow() const
    {
        return window;
    }

    void Engine::SetWindow(Window* window)
    {
        this->window = window;
    }

    bool Engine::IsRunning() const 
    {
        return m_Running && (window ? window->IsOpen() : false);
    }

    float Engine::GetDeltaTime() const 
    {
        return m_DeltaTime;
    }
}