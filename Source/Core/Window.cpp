#include "Window.h"
#include "Logger.h"

namespace Orca
{
	Window::Window(int w, int h, const std::string& t) : m_Width(w), m_Height(h), m_Title(t) 
	{
		if (!Init())
		{
			Logger::Log(LogLevel::Fatal, "Failed to initialize the Window!");
		}
	}

	Window::~Window() { Shutdown(); }

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::IsOpen() const
	{
		return !glfwWindowShouldClose(m_Window);
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			Logger::Log(LogLevel::Error, "Failed to initialize GLFW!");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

		if (!m_Window)
		{
			Logger::Log(LogLevel::Error, "Failed to create a window!");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			Logger::Log(LogLevel::Error, "Failed to initialize GLFW!");
			glfwDestroyWindow(m_Window);
			glfwTerminate();
			return false;
		}

		glViewport(0, 0, m_Width, m_Height);
		glfwSwapInterval(1);

		return true;
	}

	void Window::Shutdown()
	{
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}

		glfwTerminate();
	}
}