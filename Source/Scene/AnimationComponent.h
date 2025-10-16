#pragma once
#ifndef ORCA_ANIMATION_COMPONENT_H
#define ORCA_ANIMATION_COMPONENT_H

#include "Component.h"
#include "Asset/Animation/AnimationClip.h"
#include "SkeletonComponent.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class AnimationComponent : public Component
    {
    public:
        AnimationComponent();

        void AddClip(const std::string& name, std::shared_ptr<AnimationClip> clip);
        void Play(const std::string& name, bool loop = true);
        void Stop();
        void Update(float deltaTime);

        bool IsPlaying() const;
        std::string GetCurrentClipName() const;
        void ApplyTo(SkeletonComponent* skeleton) const;

    private:
        std::unordered_map<std::string, std::shared_ptr<AnimationClip>> m_Clips;
        std::shared_ptr<AnimationClip> m_CurrentClip;
        std::string m_CurrentClipName;
        float m_Time = 0.0f;
        bool m_Loop = true;
        bool m_Playing = false;
    };
#pragma warning(pop)
}
#endif