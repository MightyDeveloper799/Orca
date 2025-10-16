#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

#include <glm/glm.hpp>

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class Renderer 
    {
    public:
        static void Init();
        static void BeginFrame();
        static void EndFrame();

        static void DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& transform);
    };
#pragma warning(pop)
}

#endif