#include "ModelImporter.h"
#include <tiny_obj_loader.h>
#include <tiny_gltf.h>
#include <iostream>

namespace Orca
{
	Model ModelImporter::ImportFromOBJ(const std::string& filePath)
	{
		tinyobj::attrib_t attribute;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		std::string baseDirectory = filePath.substr(0, filePath.find_last_of("/\\") + 1);

		bool success = tinyobj::LoadObj(&attribute, &shapes, &materials, &warn, &err, filePath.c_str(), baseDirectory.c_str());

		if (!warn.empty()) std::cout << "" << warn << std::endl;
		if (!err.empty()) std::cout << "" << warn << std::endl;
		if (!success) return Model("InvalidOBJ");

		Model model("ImportedOBJ");

		for (const auto& shape : shapes)
		{
			Mesh mesh(shape.name);

			for (const auto& index : shape.mesh.indices)
			{
				glm::vec3 position = {
					attribute.vertices[3 * index.vertex_index + 0],
					attribute.vertices[3 * index.vertex_index + 1],
					attribute.vertices[3 * index.vertex_index + 2]
				};

				glm::vec3 normal = glm::vec3(0.0f);
				if (index.normal_index >= 0)
				{
					normal = {
						attribute.normals[3 * index.normal_index + 0],
						attribute.normals[3 * index.normal_index + 1],
						attribute.normals[3 * index.normal_index + 2]
					};
				}

				glm::vec2 uv = glm::vec2(0.0f);
				if (index.texcoord_index >= 0)
				{
					uv = {
						attribute.texcoords[3 * index.texcoord_index + 0],
						attribute.texcoords[3 * index.texcoord_index + 1]
					};
				}

				mesh.AddVertex(position, normal, uv);
			}
		}

		return model;
	}

	Model ModelImporter::ImportFromGLB(const std::string& filePath)
	{
		tinygltf::Model gltfmodel;
		tinygltf::TinyGLTF loader;
		std::string err, warn;

		bool hasAnimation = !gltfmodel.animations.empty();

		bool success = loader.LoadBinaryFromFile(&gltfmodel, &err, &warn, filePath);
		if (!success)
		{
			std::cerr << "[Orca(R)] Failed to load GLB: " << err << std::endl;
			return Model("InvalidGLB");
		}

		if (!warn.empty())
		{
			std::cout << "[WARNING]: " << warn << std::endl;
		}

		Model model("ImportedGLB");

		return model;
	}

	Model ModelImporter::ImportFromGLTF(const std::string& filePath)
	{
		tinygltf::Model gltfmodel;
		tinygltf::TinyGLTF loader;
		std::string err, warn;

		bool hasAnimation = !gltfmodel.animations.empty();

		bool success = loader.LoadASCIIFromFile(&gltfmodel, &err, &warn, filePath);
		if (!success)
		{
			std::cerr << "[Orca(R)] Failed to load GLTF: " << err << std::endl;
			return Model("InvalidGLTF");
		}

		if (!warn.empty())
		{
			std::cout << "[WARNING]: " << warn << std::endl;
		}

		Model model("ImportedGLTF");

		return model;
	}
}