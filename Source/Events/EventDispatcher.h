#pragma once

#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "Event.h"
#include "OrcaAPI.h"
#include <functional>
#include <unordered_map>
#include <vector>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API EventDispatcher
	{
	public:
		using Listener = std::function<void(const Event&)>;

		void Subscribe(EventType type, Listener listener);
		void Dispatch(const Event& event);

	private:
		std::unordered_map<EventType, std::vector<Listener>> listeners;
	};
#pragma warning(pop)
}

#endif