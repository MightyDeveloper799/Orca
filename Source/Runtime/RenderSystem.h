#pragma once

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "RuntimeContext.h"
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API RenderSystem
	{
	public:
		static void Initialize();
		static void Render(RuntimeContext& ctx);
		static void Shutdown();
	};
#pragma warning(pop)
}

#endif