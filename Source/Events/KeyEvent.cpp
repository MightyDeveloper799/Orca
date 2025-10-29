#include "KeyEvent.h"

namespace Orca
{
	KeyEvent::KeyEvent(EventType type, int keyCode)
		: Event(type)
	{
		SetData("KeyCode", to_string_generic(keyCode));
	}

	int KeyEvent::GetKeyCode() const
	{
		const std::string& data = GetData("KeyCode");
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

	KeyPressedEvent::KeyPressedEvent(int keyCode, int repeatCount)
		: KeyEvent(EventType::KeyPressed, keyCode)
	{
		SetData("RepeatCount", to_string_generic(repeatCount));
	}

	int KeyPressedEvent::GetRepeatCount() const
	{
		const std::string& data = GetData("RepeatCount");
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

	KeyReleasedEvent::KeyReleasedEvent(int keyCode)
		: KeyEvent(EventType::KeyRelease, keyCode) {}
}