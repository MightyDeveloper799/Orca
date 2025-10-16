#include "Material.h"
#include "../Renderer/ShaderRegistry.h"
#include <stdexcept>

namespace Orca
{
    Material::Material(const std::string& vertPath, const std::string& fragPath) 
        : vertPath(vertPath), fragPath(fragPath) {}
	Material::Material(const std::string& name) : name(name) {}

    void Material::SetAlbedoColor(const glm::vec3& color) 
    {
        albedoColor = color;
    }

    void Material::SetMetallic(float value) 
    {
        metallic = value;
    }

    void Material::SetRoughness(float value) 
    {
        roughness = value;
    }

    void Material::SetAlbedoTexture(const std::string& path) 
    {
        albedoTexture = path;
    }

    void Material::SetMetallicTexture(const std::string& path) 
    {
        metallicTexture = path;
    }

    void Material::SetRoughnessTexture(const std::string& path) 
    {
        roughnessTexture = path;
    }

    const std::string& Material::GetName() const 
    {
        return name;
    }

    const glm::vec3& Material::GetAlbedoColor() const 
    {
        return albedoColor;
    }

    float Material::GetMetallic() const 
    {
        return metallic;
    }

    float Material::GetRoughness() const 
    {
        return roughness;
    }

    const std::string& Material::GetAlbedoTexture() const 
    {
        return albedoTexture;
    }

    const std::string& Material::GetMetallicTexture() const 
    {
        return metallicTexture;
    }

    const std::string& Material::GetRoughnessTexture() const 
    {
        return roughnessTexture;
    }
    Shader& Material::GetShader()
    {
        Shader* shader = ShaderRegistry::Get(shaderName);
        if (!shader)
        {
            throw std::runtime_error("Material::GetShader failed! Shader not found! [" + shaderName + "]");
        }

        return *shader;
    }

    void Material::SetShaderPaths(const std::string& vertex, const std::string& fragment)
    {
        vertPath = vertex;
        fragPath = fragment;
        shader = new Shader(vertPath, fragPath);
    }

    void Material::SetShaderName(const std::string& name)
    {
        shaderName = name;
    }
}