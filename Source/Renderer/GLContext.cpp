#include "GLContext.h"
#include <iostream>

namespace Orca {

    GLFWwindow* GLContext::s_Window = nullptr;

    bool GLContext::Initialize(int width, int height, const std::string& title) 
    {
        if (!glfwInit()) 
        {
            std::cerr << "Failed to initialize GLFW\n";
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        s_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!s_Window) 
        {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(s_Window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) 
        {
            std::cerr << "Failed to initialize GLEW\n";
            return false;
        }

        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);

        return true;
    }

    void GLContext::Shutdown() 
    {
        glfwDestroyWindow(s_Window);
        glfwTerminate();
    }

    void GLContext::PollEvents() 
    {
        glfwPollEvents();
    }

    bool GLContext::WindowShouldClose() 
    {
        return glfwWindowShouldClose(s_Window);
    }

    void GLContext::SwapBuffers() 
    {
        glfwSwapBuffers(s_Window);
    }

    GLFWwindow* GLContext::GetWindow() 
    {
        return s_Window;
    }
}