#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Timer.h"
#include "../OrcaAPI.h"
#include "../Events/WindowEvent.h"
#include "../Layer/LayerStack.h"
#include "../Events/Event.h"
#include <memory>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class Window;

	class ORCA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(std::unique_ptr<Layer> layer);
		void PushOverlay(std::unique_ptr<Layer> overlay);

		void OnEvent(Event& event);

		bool OnWindowClose(Event& event);
		bool OnWindowResize(Event& event);

		static Application& Get() { return *s_Instance; }

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		LayerStack m_Stack;
		Timer m_timer;
		bool m_Running = true;
		float m_LastFrameTime = 0.0f;
	};

	Application* CreateApplication();
#pragma warning(pop)
}

#endif