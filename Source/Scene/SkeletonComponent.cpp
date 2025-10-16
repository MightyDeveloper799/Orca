#include "SkeletonComponent.h"

namespace Orca {

    void SkeletonComponent::AddBone(const std::string& name) 
    {
        if (!HasBone(name))
        {
            m_Bones[name] = Bone{ name, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f) };
        }
    }

    bool SkeletonComponent::HasBone(const std::string& name) const 
    {
        return m_Bones.find(name) != m_Bones.end();
    }

    void SkeletonComponent::SetBoneTransform(const std::string& name, const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale) 
    {
        if (HasBone(name)) 
        {
            m_Bones[name].position = pos;
            m_Bones[name].rotation = rot;
            m_Bones[name].scale = scale;
        }
    }

    const Bone* SkeletonComponent::GetBone(const std::string& name) const 
    {
        auto it = m_Bones.find(name);
        return (it != m_Bones.end()) ? &it->second : nullptr;
    }

    void SkeletonComponent::ApplyPose(const std::unordered_map<std::string, float>& boneTransforms) 
    {
        for (const auto& [name, value] : boneTransforms) 
        {
            if (HasBone(name)) 
            {
                glm::quat rot = glm::angleAxis(glm::radians(value), glm::vec3(0, 1, 0));
                SetBoneTransform(name, m_Bones[name].position, rot, m_Bones[name].scale);
            }
        }
    }
}