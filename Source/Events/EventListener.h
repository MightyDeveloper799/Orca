#pragma once

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "Event.h"
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API EventListener
	{
	public:
		virtual ~EventListener() = default;
		virtual void OnEvent(const Event& event) = 0;
	};
#pragma warning(pop)
}

#endif