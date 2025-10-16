#pragma once

#ifndef SCRIPT_SYSTEM_H
#define SCRIPT_SYSTEM_H

#include "Runtime/RuntimeContext.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ScriptSystem
	{
	public:
		static void Initialize(RuntimeContext& ctx);
		static void Execute(RuntimeContext& ctx);
		static void Shutdown();
	};
#pragma warning(pop)
}

#endif
