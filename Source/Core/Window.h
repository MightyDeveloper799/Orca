#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API Window
	{
		using WindowHandle = GLFWwindow*;
	public:
		Window(int w, int h, const std::string& title);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		void OnUpdate();
		bool IsOpen() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		inline WindowHandle GetNativeWindow() const { return m_Window; }

	private:
		WindowHandle m_Window = nullptr;
		std::string m_Title;
		int m_Width, m_Height;

		bool Init();
		void Shutdown();
	};
}

#endif