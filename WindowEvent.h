#pragma once

#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "Event.h"
#include "../OrcaAPI.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include "../Utilities/ToStringUtil.h"

namespace Orca
{
	class ORCA_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() : Event(EventType::WindowClose) {}
		std::string GetName() const override { return "WindowClose"; }

		EventType GetEventType() const override { return EventType::WindowClose; }
	};

	class ORCA_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height);
		std::string GetName() const override { return "WindowResize"; }

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		EventType GetEventType() const override { return EventType::WindowClose; }
	};
}

#endif