#pragma once

#ifndef ANIMATION_CLIP_H
#define ANIMATION_CLIP_H

#include <string>
#include <vector>
#include <unordered_map>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class SkeletonComponent;

	struct Keyframe
	{
		float time;
		std::unordered_map<std::string, float> boneTransforms;
	};

	class AnimationClip
	{
	public:
		AnimationClip(const std::string& name, float duration);

		void AddKeyframe(const Keyframe& frame);
		void SetDuration(float duration);
		const std::vector<Keyframe>& GetKeyframes() const;
		float GetDuration() const;
		const std::string& GetName() const;

		void Apply(float time, SkeletonComponent* skeleton) const;

	private:
		std::string name;
		float duration;
		std::vector<Keyframe> keyframes;
	};
}

#endif