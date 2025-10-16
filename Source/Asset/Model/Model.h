#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Renderer/Mesh.h"
#include "Material/Material.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class Model
	{
	public:
		Model(const std::string& name);

		void AddMesh(const Mesh& mesh);
		void AddMaterial(const Material& mat);

		const std::string& GetName() const;
		const std::vector<Mesh>& GetMesh() const;
		const std::vector<Material>& GetMaterial() const;

	private:
		std::string name;
		std::vector<Mesh> meshes;
		std::vector<Material> materials;
	};
#pragma warning(pop)
}

#endif