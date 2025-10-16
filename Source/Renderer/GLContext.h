#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class GLContext
	{
	public:
		static bool Initialize(int width, int height, const std::string& title);
		static void Shutdown(void);
		static void PollEvents(void);
		static bool WindowShouldClose();
		static void SwapBuffers(void);

		static GLFWwindow* GetWindow();
	private:
		static GLFWwindow* s_Window;
	};
#pragma warning(pop)
}