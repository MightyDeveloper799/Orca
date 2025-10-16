#include "CameraSystem.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Entity.h"
#include "../Scene/TransformComponent.h"
#include "../Scene/CameraComponent.h"

namespace Orca 
{
    Entity* CameraSystem::s_ActiveCamera = nullptr;

    void CameraSystem::Initialize() 
    {
        std::shared_ptr<Scene> scene = SceneManager::GetActiveScene();
        if (!scene) return;

        for (auto& entityPtr : scene->GetEntities()) 
        {
            if (entityPtr->HasComponent<CameraComponent>()) 
            {
                s_ActiveCamera = entityPtr.get();
                break;
            }
        }
    }

    void CameraSystem::Shutdown() 
    {
        s_ActiveCamera = nullptr;
    }

    void CameraSystem::Update(RuntimeContext& context) 
    {
        if (!s_ActiveCamera->IsValid()) return;

        std::shared_ptr<Scene> scene = SceneManager::GetActiveScene();
        if (!scene) return;

        const auto& transform = s_ActiveCamera->GetComponent<TransformComponent>();
        const auto& camera = s_ActiveCamera->GetComponent<CameraComponent>();

        Matrix4 view = camera->GetViewMatrix();
        Matrix4 proj = camera->GetProjectionMatrix();
        Vector3 pos = transform->GetPosition();

        context.SetViewMatrix(view);
        context.SetProjectionMatrix(proj);
        context.SetCameraPosition(pos);
    }

    Entity* CameraSystem::GetActiveCamera() 
    {
        return s_ActiveCamera;
    }

    void CameraSystem::SetActiveCamera(Entity camera) 
    {
        if (camera.IsValid() && camera.HasComponent<CameraComponent>()) 
        {
            s_ActiveCamera = &camera;
        }
    }

}