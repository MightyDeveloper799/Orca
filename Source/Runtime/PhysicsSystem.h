#pragma once

#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "Runtime/RuntimeContext.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class PhysicsSystem
	{
	public:
		static void Initialize();
		static void Update(RuntimeContext& ctx);
		static void Shutdown();
	};
#pragma warning(pop)
}

#endif