#include "Model.h"

namespace Orca {

    Model::Model(const std::string& name)
        : name(name) {}

    void Model::AddMesh(const Mesh& mesh) 
    {
        meshes.push_back(mesh);
    }

    void Model::AddMaterial(const Material& material) 
    {
        materials.push_back(material);
    }

    const std::string& Model::GetName() const 
    {
        return name;
    }

    const std::vector<Mesh>& Model::GetMesh() const 
    {
        return meshes;
    }

    const std::vector<Material>& Model::GetMaterial() const 
    {
        return materials;
    }
}