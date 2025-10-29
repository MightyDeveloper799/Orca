#include "Application.h"
#include "Timer.h"
#include "../Events/EventDispatcher.h"
#include "Logger.h"
#include "Window.h"

namespace Orca
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		if (s_Instance)
		{
			Logger::Log(LogLevel::Fatal, "Application already exists!");
		}
		s_Instance = this;

		m_Window = std::make_unique<Window>(1280, 720, "Orca Engine");
		m_Window->SetEventCallback([this](Event& e)
			{
				this->OnEvent(e);
			});
	}

	Application::~Application()
	{
		Logger::Log(LogLevel::Info, "Application shutting down.");
	}

	void Application::PushLayer(std::unique_ptr<Layer> layer)
	{
		m_Stack.PushLayer(std::move(layer));
	}

	void Application::PushOverlay(std::unique_ptr<Layer> overlay)
	{
		m_Stack.PushOverlay(std::move(overlay));
	}

	void Application::OnEvent(Event& e)
	{
		if (e.GetEventType() == EventType::WindowClose)
		{
			if (OnWindowClose(e))
			{
				e.m_Handled = true;
			}
		}
		else if (e.GetEventType() == EventType::WindowResize)
		{
			if (OnWindowResize(e))
			{
				e.m_Handled = true;
			}
		}

		for (auto it = m_Stack.rbegin(); it != m_Stack.rend(); ++it)
		{
			if (e.m_Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_Running = false;
		Logger::Log(LogLevel::Info, "Window closed.");
		return true;
	}

	bool Application::OnWindowResize(Event& e)
	{
		Orca::WindowResizeEvent& resizeEvent = static_cast<Orca::WindowResizeEvent&>(e);

		unsigned int width = resizeEvent.GetWidth();
		unsigned int height = resizeEvent.GetHeight();

		e.m_Handled = true;

		return true;
	}

	void Application::Run()
	{
		Logger::Log(LogLevel::Info, "Orca Engine started running...");

		while (m_Running)
		{
			float time = m_timer.GetTime();
			float deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (auto& layer : m_Stack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}
}