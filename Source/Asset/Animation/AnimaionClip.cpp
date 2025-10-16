#include "AnimationClip.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include "Scene/SkeletonComponent.h"

namespace Orca
{
	AnimationClip::AnimationClip(const std::string& name, float duration) : name(name), duration(duration) {}

	void AnimationClip::AddKeyframe(const Keyframe& frame)
	{
		keyframes.push_back(frame);
	}

	void AnimationClip::SetDuration(float duration)
	{
		this->duration = duration;
	}

	const std::vector<Keyframe>& AnimationClip::GetKeyframes() const
	{
		return keyframes;
	}

	float AnimationClip::GetDuration() const
	{
		return duration;
	}

	const std::string& AnimationClip::GetName() const
	{
		return name;
	}

	void AnimationClip::Apply(float dt, SkeletonComponent* skeleton) const
	{
		if (keyframes.empty()) return;

		float currentClipTime = std::fmod(dt, duration);

		const Keyframe* prev = nullptr;
		const Keyframe* next = nullptr;

		for (size_t i = 0; i < keyframes.size(); i++)
		{
			if (keyframes[i].time >= currentClipTime)
			{
				next = &keyframes[i];
				if (i > 0)
					prev = &keyframes[i - 1];
				else
					prev = &keyframes.back();
				break;
			}
		}

		if (!next)
		{
			prev = &keyframes.back();
			next = &keyframes.back();
		}

		if (!prev || !next)
		{
			for (const auto& [boneName, value] : keyframes.back().boneTransforms)
			{
				glm::vec3 pos = skeleton->GetBone(boneName)->position;
				glm::vec3 scale = skeleton->GetBone(boneName)->scale;
				glm::quat rot = glm::angleAxis(glm::radians(value), glm::vec3(0, 1, 0));

				skeleton->SetBoneTransform(boneName, pos, rot, scale);
			}

			return;
		}

		float timePrev = prev->time;
		float timeNext = next->time;

		if (timeNext < timePrev)
		{
			timeNext += duration;
		}

		float segmentDuration = timeNext - timePrev;

		float t = (segmentDuration > 0.0f) ? (currentClipTime - timePrev) / segmentDuration : 0.0f;
		t = std::max(0.0f, std::min(1.0f, t));

		for (const auto& [boneName, valueNext] : next->boneTransforms)
		{
			float valuePrev = 0.0f;
			if (prev->boneTransforms.count(boneName)) {
				valuePrev = prev->boneTransforms.at(boneName);
			}

			float interpolatedValue = valuePrev + t * (valueNext - valuePrev);

			float angleRadians = glm::radians(interpolatedValue);
			glm::quat rot = glm::angleAxis(angleRadians, glm::vec3(0, 1, 0));

			glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
			glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

			skeleton->SetBoneTransform(boneName, pos, rot, scale);
		}
	}
}