#pragma once

#ifndef MOUSE_EVENTS_H
#define MOUSE_EVENTS_H

#include "Event.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <functional>
#include "../Utilities/ToStringUtil.h"

namespace Orca
{
    class ORCA_API MouseEvent : public Event
    {
    protected:
        MouseEvent(EventType type, const std::string& name, float x, float y);

    public:
        float GetX() const;
        float GetY() const;
    };

    class ORCA_API MouseMovedEvent : public MouseEvent
    {
    public:
        MouseMovedEvent(float x, float y);
    };

    class ORCA_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset);

        float GetXOffset() const;
        float GetYOffset() const;
    };

    class ORCA_API MouseButtonEvent : public Event
    {
    protected:
        MouseButtonEvent(EventType type, const std::string& name, int buttonCode);

    public:
        int GetButtonCode() const;
    };

    class ORCA_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int buttonCode);
    };

    class ORCA_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int buttonCode);
    };

}

#endif