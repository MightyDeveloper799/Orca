#include "WindowEvent.h"

namespace Orca
{
	WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
		: Event(EventType::WindowResize)
	{
		SetData("Width", to_string_generic(width));
		SetData("Height", to_string_generic(height));
	}

	unsigned int WindowResizeEvent::GetWidth() const
	{
		const std::string& data = GetData("Width");
		if (data.empty()) return 0;
		try
		{
			return static_cast<unsigned int>(std::stoul(data));
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	unsigned int WindowResizeEvent::GetHeight() const
	{
		const std::string& data = GetData("Height");
		if (data.empty()) return 0;
		try
		{
			return static_cast<unsigned int>(std::stoul(data));
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}
}