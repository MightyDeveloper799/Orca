#include "EventDispatcher.h"

namespace Orca
{
	void EventDispatcher::Subscribe(EventType type, Listener listener)
	{
		listeners[type].push_back(listener);
	}

	void EventDispatcher::Dispatch(const Event& event)
	{
		auto it = listeners.find(event.GetType());
		if (it != listeners.end())
		{
			for (auto& listener : it->second)
			{
				listener(event);
			}
		}
	}
}