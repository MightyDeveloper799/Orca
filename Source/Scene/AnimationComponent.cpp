#include "AnimationComponent.h"

namespace Orca {

    AnimationComponent::AnimationComponent() {}

    void AnimationComponent::AddClip(const std::string& name, std::shared_ptr<AnimationClip> clip)
    {
        m_Clips[name] = clip;
    }

    void AnimationComponent::Play(const std::string& name, bool loop) 
    {
        auto it = m_Clips.find(name);
        if (it != m_Clips.end()) 
        {
            m_CurrentClip = it->second;
            m_CurrentClipName = name;
            m_Time = 0.0f;
            m_Loop = loop;
            m_Playing = true;
        }
    }

    void AnimationComponent::Stop() 
    {
        m_Playing = false;
        m_CurrentClip = nullptr;
        m_CurrentClipName.clear();
        m_Time = 0.0f;
    }

    void AnimationComponent::Update(float deltaTime)
    {
        if (!m_Playing || !m_CurrentClip) return;

        m_Time += deltaTime;
        if (m_Time > m_CurrentClip->GetDuration()) 
        {
            if (m_Loop) 
            {
                m_Time = fmod(m_Time, m_CurrentClip->GetDuration());
            }
            else 
            {
                Stop();
            }
        }

        m_CurrentClip->Apply(m_Time, nullptr);
    }

    bool AnimationComponent::IsPlaying() const 
    {
        return m_Playing;
    }

    std::string AnimationComponent::GetCurrentClipName() const 
    {
        return m_CurrentClipName;
    }

    void AnimationComponent::ApplyTo(SkeletonComponent* skeleton) const
    {
        if (!m_Playing || !m_CurrentClip || !skeleton) return;

        m_CurrentClip->Apply(m_Time, skeleton);
    }
}