#pragma once

#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "Component.h"
#include "Renderer/Mesh.h"
#include "Material/Material.h"
#include "Math/Bounds.h"
#include <memory>

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class MeshComponent : public Component 
    {
    public:
        MeshComponent() = default;
        MeshComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material = nullptr);

        void SetMesh(std::shared_ptr<Mesh> mesh);
        void SetMaterial(std::shared_ptr<Material> material);

        std::shared_ptr<Mesh> GetMesh() const { return m_Mesh; }
        std::shared_ptr<Material> GetMaterial() const { return m_Material; }

        std::string GetMeshPath() const { return m_Mesh ? m_Mesh->GetName() : "None"; }
        std::string GetMaterialPath() const { return m_Material ? m_Material->GetName() : "None"; }

        const Bounds& GetBounds() const;

        void Draw() const;

    private:
        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Material> m_Material;
        Bounds m_Bounds;
    };

}

#endif