#pragma once

#ifndef SKELETON_COMPONENT_H
#define SKELETON_COMPONENT_H

#include "Component.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	struct Bone
	{
		std::string name;
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
	};

	class SkeletonComponent : public Component
	{
	public:
		void AddBone(const std::string& name);
		bool HasBone(const std::string& name) const;

		void SetBoneTransform(const std::string& name, const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale);
		const Bone* GetBone(const std::string& name) const;

		void ApplyPose(const std::unordered_map<std::string, float>& boneTransforms);

	private:
		std::unordered_map<std::string, Bone> m_Bones;
	};
#pragma warning(pop)
}

#endif