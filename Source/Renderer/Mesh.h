#pragma once

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>

#include "../Math/Bounds.h"
#include "../OrcaAPI.h"
#include "Vertex.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		Mesh(const std::string& name);
		~Mesh();

		static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		void Bind() const;
		void Unbind() const;
		void Draw() const;

		void AddVertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv)
		{
			Vertex v{};
			v.Position = pos;
			v.Normal = normal;
			v.TexCoords = uv;
			m_Vertices.push_back(v);
		}

		const Bounds& GetBounds() const;

		std::string GetName() const { return name; }
		void SetName(std::string name);

		bool IsRenderable() const;

		void AddIndex(unsigned int index) { m_Indices.push_back(index); }
		unsigned int GetVertexCount() const { return static_cast<unsigned int>(m_Vertices.size()); }

	private:
		unsigned int m_VAO, m_VBO, m_EBO;
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::string name;

		mutable Bounds bounds;
		mutable bool m_BoundsDirty = true;

		bool m_Initialized = false;

		void SetupMesh();
	};
}

#endif