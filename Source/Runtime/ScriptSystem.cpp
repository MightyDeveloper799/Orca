#include "ScriptSystem.h"
#include "../Scripting/ScriptComponent.h"
#include "../Scene/Entity.h"
#include "../Scene/Scene.h"
#include "../Core/Logger.h"

namespace Orca
{
	void ScriptSystem::Initialize(RuntimeContext& ctx)
    {
        try
        {
            std::shared_ptr<Scene> initialScene = std::make_shared<Scene>(ctx);

            ctx.SetActiveScene(initialScene);
        }
        catch (const std::exception& e)
        {
            Logger::Log(LogLevel::Fatal, "ScriptSystem::Initialize failed during scene creation: " + std::string(e.what()));
            throw;
        }
    }

    void ScriptSystem::Execute(RuntimeContext& ctx) 
    {
        std::shared_ptr<Scene> scene = ctx.GetActiveSceneShared();

        if (!scene)
        {
            Logger::Log(LogLevel::Warning, "ScriptSystem::Execute skipped, no active scene found!");
            return;
        }

        for (auto& entity : scene->GetEntitiesWith<ScriptComponent>()) 
        {
            ScriptComponent* script = entity->GetComponent<ScriptComponent>();
            if (script && script->IsValid())
            {
                script->Invoke("OnUpdate", ctx.GetDeltaTime());
            }
        }
    }

    void ScriptSystem::Shutdown() 
    {
        // Shutdown VM, release script handles
    }
}