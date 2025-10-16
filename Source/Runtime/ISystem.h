#pragma once

#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "RuntimeContext.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ISystem
	{
	public:
		virtual void Update(RuntimeContext& ctx) = 0;
		virtual void Render(RuntimeContext& gtx) = 0;
		virtual ~ISystem() = default;
	};
#pragma warning(pop)
}

#endif