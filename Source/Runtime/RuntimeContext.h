#pragma once

#ifndef RUNTIME_CONTEXT_H
#define RUNTIME_CONTEXT_H

#include <memory>
#include "../OrcaAPI.h"

namespace Orca
{
    class Scene;
    class Entity;
    struct Matrix4;
    struct Vector3;
    class TransformComponent;
    class InputState;

#pragma warning(push)
#pragma warning(disable: 4251)

    struct ORCA_API RuntimeContext
    {
    public:
        RuntimeContext();
        ~RuntimeContext();
        RuntimeContext(RuntimeContext&&) noexcept;
        RuntimeContext& operator=(RuntimeContext&&) noexcept;

        RuntimeContext(const RuntimeContext&) = delete;
        RuntimeContext& operator=(const RuntimeContext&) = delete;

        void SetActiveScene(std::shared_ptr<Scene> scene);
        const Scene* GetActiveScene() const;

        float GetDeltaTime() const;
        void SetDeltaTime(float dt);

        std::shared_ptr<Scene> GetActiveSceneShared();
        const std::shared_ptr<const Scene> GetActiveSceneShared() const;

        bool IsPaused() const;
        void SetPaused(bool paused);

        void SetViewMatrix(const Matrix4& matrix);
        void SetProjectionMatrix(const Matrix4& matrix);
        void SetCameraPosition(const Vector3& position);

        const Matrix4& GetViewMatrix() const;
        const Matrix4& GetProjectionMatrix() const;
        const TransformComponent& GetCameraTransform() const;
        const Vector3& GetCameraPosition() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
#pragma warning(pop)
}

#endif