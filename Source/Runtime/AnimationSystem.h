#pragma once

#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "ISystem.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class AnimationSystem : public ISystem
	{
	public:
		void Update(RuntimeContext& ctx) override;
		void Render(RuntimeContext& ctx) override {}
	};
#pragma warning(pop)
}

#endif