#include "AnimationSystem.h"
#include "../Asset/Object/ObjectManager.h"
#include "../Scene/AnimationComponent.h"
#include "../Scene/SkeletonComponent.h"
#include "../Scene/Scene.h"

namespace Orca
{
	void AnimationSystem::Update(RuntimeContext& gtx)
	{
		for (const auto& obj : gtx.GetActiveScene()->GetObjects())
		{
			const auto& anim = obj->GetComponent<AnimationComponent>();
			if (anim && anim->IsPlaying())
			{
				auto skeleton = obj->GetComponent<SkeletonComponent>();
				if (skeleton)
				{
					anim->Update(gtx.GetDeltaTime());
					anim->ApplyTo(skeleton.get());
				}
			}
		}
	}
}