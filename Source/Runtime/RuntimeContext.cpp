#include "RuntimeContext.h"
#include "../Math/Matrix4.h"
#include "../Math/Vector3.h"
#include "../Scene/Entity.h"
#include "../Scene/Scene.h"
#include "../Scene/TransformComponent.h"
#include "../Core/InputState.h"
#include <stdexcept>

namespace Orca
{
    struct RuntimeContext::Impl
    {
        float deltaTime = 0.0f;
        std::shared_ptr<Scene> activeScene = nullptr;

        Matrix4 ViewMatrix = {};
        Matrix4 ProjectionMatrix = {};
        TransformComponent CameraPosition;
        Vector3 CameraPosition_Vec3;

        bool isPaused = false;

        InputState inputState;
    };

    inline RuntimeContext::RuntimeContext() : pImpl(std::make_unique<Impl>()) {}

    inline RuntimeContext::~RuntimeContext() = default;

    inline RuntimeContext::RuntimeContext(RuntimeContext&&) noexcept = default;
    inline RuntimeContext& RuntimeContext::operator=(RuntimeContext&&) noexcept = default;

    void RuntimeContext::SetActiveScene(std::shared_ptr<Scene> scene)
    {
        pImpl->activeScene = scene;
    }

    const Scene* RuntimeContext::GetActiveScene() const
    {
        return pImpl->activeScene.get();
    }

    std::shared_ptr<Scene> RuntimeContext::GetActiveSceneShared()
    {
        return pImpl->activeScene;
    }

    const std::shared_ptr<const Scene> RuntimeContext::GetActiveSceneShared() const
    {
        return std::const_pointer_cast<const Scene>(pImpl->activeScene);
    }

    float RuntimeContext::GetDeltaTime() const
    {
        return pImpl->deltaTime;
    }

    void RuntimeContext::SetDeltaTime(float dt)
    {
        pImpl->deltaTime = dt;
    }

    bool RuntimeContext::IsPaused() const
    {
        return pImpl->isPaused;
    }

    void RuntimeContext::SetPaused(bool paused)
    {
        pImpl->isPaused = paused;
    }

    void RuntimeContext::SetViewMatrix(const Matrix4& matrix)
    {
        pImpl->ViewMatrix = matrix;
    }

    void RuntimeContext::SetProjectionMatrix(const Matrix4& matrix)
    {
        pImpl->ProjectionMatrix = matrix;
    }

    void RuntimeContext::SetCameraPosition(const Vector3& position)
    {
        pImpl->CameraPosition.SetPosition(position);
        pImpl->CameraPosition_Vec3 = position;
    }

    const Matrix4& RuntimeContext::GetViewMatrix() const
    {
        return pImpl->ViewMatrix;
    }

    const Matrix4& RuntimeContext::GetProjectionMatrix() const
    {
        return pImpl->ProjectionMatrix;
    }

    const TransformComponent& RuntimeContext::GetCameraTransform() const
    {
        return pImpl->CameraPosition;
    }

    const Vector3& RuntimeContext::GetCameraPosition() const
    {
        return pImpl->CameraPosition_Vec3;
    }
}