#include "AppEvent.h"

namespace Orca
{
	AppTickEvent::AppTickEvent() : Event(EventType::Tick) {}

	AppUpdateEvent::AppUpdateEvent() : Event(EventType::Update) {}

	AppRenderEvent::AppRenderEvent() : Event(EventType::Render) {}
}