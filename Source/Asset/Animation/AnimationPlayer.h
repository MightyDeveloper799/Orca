#pragma once

#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include "AnimationClip.h"
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API AnimationPlayer
	{
	public:
		AnimationPlayer();

		void Play(const AnimationClip& clip, bool loop = false);
		void Stop();
		void Update(float deltaTime);

		float GetPlaybackTime() const;
		bool IsPlaying() const;
	private:
		const AnimationClip* currentClip;
		float playbackTime;
		bool looping, playing;
	};
#pragma warning(pop)
}

#endif