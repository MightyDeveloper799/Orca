#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <glm/glm.hpp>
#include "Renderer/Shader.h"
#include "../OrcaAPI.h"
#include <memory>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API Material
	{
	public:
        Material(const std::string& vertPath, const std::string& fragPath);
		Material(const std::string& name);	

        void SetAlbedoColor(const glm::vec3& color);
        void SetMetallic(float value);
        void SetRoughness(float value);

        void SetAlbedoTexture(const std::string& path);
        void SetMetallicTexture(const std::string& path);
        void SetRoughnessTexture(const std::string& path);

        const std::string& GetName() const;
        const glm::vec3& GetAlbedoColor() const;
        float GetMetallic() const;
        float GetRoughness() const;

        const std::string& GetAlbedoTexture() const;
        const std::string& GetMetallicTexture() const;
        const std::string& GetRoughnessTexture() const;

        Shader& GetShader();
        void SetShaderPaths(const std::string& vertex, const std::string& fragment);
        void SetShaderName(const std::string& name);

    private:
        std::string name;
        std::string shaderName;

        glm::vec3 albedoColor = glm::vec3(1.0f);
        float metallic = 0.0f;
        float roughness = 1.0f;

        std::string vertPath, fragPath;

        Shader* shader = new Shader(vertPath, fragPath);

        std::string albedoTexture, metallicTexture, roughnessTexture;
	};
}

#endif