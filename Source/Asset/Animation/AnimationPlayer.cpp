#include "AnimationPlayer.h"

namespace Orca
{
	AnimationPlayer::AnimationPlayer() 
		: currentClip(nullptr), playbackTime(0.0f), looping(false), playing(false) {}

	void AnimationPlayer::Play(const AnimationClip& clip, bool loop)
	{
		currentClip = &clip;
		playbackTime = 0.0f;
		looping = loop;
		playing = true;
	}

	void AnimationPlayer::Stop()
	{
		currentClip = nullptr;
		playbackTime = 0.0f;
		playing = false;
	}

	void AnimationPlayer::Update(float deltaTime) 
	{
		if (!playing || !currentClip) return;

		playbackTime += deltaTime;
		if (playbackTime > currentClip->GetDuration()) 
		{
			if (looping) playbackTime = 0.0f;
			else Stop();
		}
	}

	float AnimationPlayer::GetPlaybackTime() const 
	{
		return playbackTime;
	}

	bool AnimationPlayer::IsPlaying() const 
	{
		return playing;
	}
}