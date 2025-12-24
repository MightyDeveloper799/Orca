/*********************************************
*
* Copyright © 2025 VEGA Enterprises LTD,.
* Licensed under the MIT License.
*
**********************************************/

#include "GLRenderer.h"
#include <GL/glew.h>
#include "Core/Logger.h"
#include <GLFW/glfw3.h>

namespace Orca
{
    void GLRenderer::Initialize(void* windowHandle)
    {
        this->windowHandle = windowHandle;

        // windowHandle is actually a GLFWwindow*
        GLFWwindow* window = static_cast<GLFWwindow*>(windowHandle);
        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE; // Ensures modern features are available
        if (glewInit() != GLEW_OK)
        {
            Logger::Log(LogLevel::Error, "Failed to initialize GLEW");
            return;
        }

        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, 640, 320); // Match your App.cpp resolution

        isInitialized = true;
        Logger::Log(LogLevel::Info, "GLRenderer Initialized Successfully");
    }

    void GLRenderer::BeginFrame()
    {
        // Monokai Dark Grey background
        glClearColor(0.153f, 0.157f, 0.133f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderer::Render()
    {
        // Logic for batch rendering meshesToRender would go here
    }

    void GLRenderer::DrawMesh(const Mesh& mesh, const Shader& shader, const Matrix4& transform)
    {
        shader.Bind();
        shader.SetMat4("u_Model", transform);

        mesh.Bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        mesh.Unbind();

        shader.Unbind();
    }

    void GLRenderer::EndFrame()
    {
		glfwSwapBuffers(static_cast<GLFWwindow*>(windowHandle));
        glfwPollEvents();
    }

    void GLRenderer::Shutdown()
    {
        isInitialized = false;
    }

    void GLRenderer::SubmitMesh(const Mesh& mesh)
    {
        meshesToRender.push_back(&mesh);
    }

    bool GLRenderer::CompileAndLinkShaders()
    {
        // Basic shader compilation logic
        return true;
    }
}