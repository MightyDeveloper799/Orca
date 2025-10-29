#pragma once

#ifndef APP_EVENT_H
#define APP_EVENT_H

#include "Event.h"
#include "../OrcaAPI.h"

namespace Orca
{
	class ORCA_API AppTickEvent : public Event
	{
	public:
		AppTickEvent();
	};

	class ORCA_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent();
	};

	class ORCA_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent();
	};
}

#endif