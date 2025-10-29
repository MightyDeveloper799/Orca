#pragma once

#ifndef KEY_EVENTS_H
#define KEY_EVENTS_H

#include "Event.h"
#include <string>
#include <stdexcept>
#include "../Utilities/ToStringUtil.h"

namespace Orca 
{
    class ORCA_API KeyEvent : public Event
    {
    protected:
        KeyEvent(EventType type, int keyCode);

    public:
        int GetKeyCode() const;
    };

    class ORCA_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, int repeatCount);

        int GetRepeatCount() const;

        bool IsRepeat() const { return GetRepeatCount() > 0; }
    };

    class ORCA_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode);
    };

}

#endif