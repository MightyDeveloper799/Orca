#include "MeshComponent.h"
#include "../Core/Logger.h"

namespace Orca {

    MeshComponent::MeshComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
        : m_Mesh(mesh), m_Material(material)
    {
        if (mesh)
        {
            m_Bounds = mesh->GetBounds();
        }
    }

    void MeshComponent::SetMesh(std::shared_ptr<Mesh> mesh) 
    {
        m_Mesh = mesh;
        if (mesh) {
            m_Bounds = mesh->GetBounds();
        }
    }

    void MeshComponent::SetMaterial(std::shared_ptr<Material> material) 
    {
        m_Material = material;
    }

    const Bounds& MeshComponent::GetBounds() const 
    {
        return m_Bounds;
    }

    void MeshComponent::Draw() const 
    {
        if (!m_Mesh) 
        { 
            Logger::Log(LogLevel::Warning, "Draw skipped: m_Mesh isn't initialized/is null."); 
            return; 
        } 

        m_Mesh->Draw();
    }
}