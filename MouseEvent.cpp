#include "MouseEvent.h"
#include <stdexcept>

namespace Orca
{
    MouseEvent::MouseEvent(EventType type, const std::string& name, float x, float y)
        : Event(type)
    {
        SetData("MousePositionX", to_string_generic(x));
        SetData("MousePositionY", to_string_generic(y));
    }

    float MouseEvent::GetX() const
    {
        const std::string& data = GetData("MousePositionX");
        if (data.empty()) return 0.0f;
        try 
        {
            return std::stof(data);
        }
        catch (const std::exception&) 
        {
            return 0.0f;
        }
    }

    float MouseEvent::GetY() const
    {
        const std::string& data = GetData("MousePositionY");
        if (data.empty()) return 0.0f;
        try 
        {
            return std::stof(data);
        }
        catch (const std::exception&) 
        {
            return 0.0f;
        }
    }

    MouseMovedEvent::MouseMovedEvent(float x, float y)
        : MouseEvent(EventType::MouseMoved, "MouseMoved", x, y) {
    }

    MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset)
        : Event(EventType::MouseScrolled)
    {
        // Store scroll offsets
        SetData("XOffset", to_string_generic(xOffset));
        SetData("YOffset", to_string_generic(yOffset));
    }

    float MouseScrolledEvent::GetXOffset() const
    {
        const std::string& data = GetData("XOffset");
        if (data.empty()) return 0.0f;
        try {
            return std::stof(data);
        }
        catch (const std::exception&) {
            return 0.0f;
        }
    }

    float MouseScrolledEvent::GetYOffset() const
    {
        const std::string& data = GetData("YOffset");
        if (data.empty()) return 0.0f;
        try {
            return std::stof(data);
        }
        catch (const std::exception&) {
            return 0.0f;
        }
    }

    MouseButtonEvent::MouseButtonEvent(EventType type, const std::string& name, int buttonCode)
        : Event(type)
    {
        SetData("ButtonCode", to_string_generic(buttonCode));
    }

    int MouseButtonEvent::GetButtonCode() const
    {
        const std::string& data = GetData("ButtonCode");
        if (data.empty()) return 0;
        try 
        {
            return std::stoi(data);
        }
        catch (const std::exception&) 
        {
            return 0;
        }
    }

    MouseButtonPressedEvent::MouseButtonPressedEvent(int buttonCode)
        : MouseButtonEvent(EventType::MouseButtonPressed, "MouseButtonPressed", buttonCode) {}

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(int buttonCode)
        : MouseButtonEvent(EventType::MouseButtonReleased, "MouseButtonRelease", buttonCode) {}
}