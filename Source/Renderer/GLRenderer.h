/*********************************************
*
* Copyright © 2025 VEGA Enterprises LTD,.
* Licensed under the MIT License.
*
**********************************************/

#pragma once

#include "Renderer.h"
#include <vector>
#include "Mesh.h"

#ifndef GL_RENDERER_H
#define GL_RENDERER_H

namespace Orca
{
	class GLRenderer : public Renderer
	{
    public:
        GLRenderer() = default;
        virtual ~GLRenderer() override;

        // Implementation of the Renderer Interface
        void Initialize(void* windowHandle) override;
        void Shutdown() override;
        void BeginFrame() override;
        void Render() override;
        void EndFrame() override;

        void DrawMesh(const Mesh& mesh, const Shader& shader, const Matrix4& transform) override;

        // GL Specifics
        void SubmitMesh(const Mesh& mesh);

    private:
        bool isInitialized = false;
        unsigned int programID = 0;
        std::vector<const Mesh*> meshesToRender;
        void* windowHandle;

        bool CompileAndLinkShaders();
	};
}

#endif