#include "Mesh.h"
#include <GL/glew.h>
#include <Core/Logger.h>

namespace Orca 
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
        : m_Vertices(vertices), m_Indices(indices), m_VAO(0), m_VBO(0), m_EBO(0) 
    {
        SetupMesh();
    }

    Mesh::Mesh(const std::string& name)
        : m_VAO(0), m_VBO(0), m_EBO(0), name(name)
    {
        // SetupMesh();
    }

    Mesh::~Mesh() 
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void Mesh::SetupMesh() 
    {
        if (m_Initialized) 
        {
            Logger::Log(LogLevel::Warning, "SetupMesh called on already initialized mesh.");
            return;
        }

        if (m_Indices.empty())
        {
            std::string message = "Mesh setup skipped: '" + name + "' has no indices provided.";
            Logger::Log(LogLevel::Warning, message);
            return;
        }

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);

        m_Initialized = true;
    }

    void Mesh::Bind() const 
    {
        glBindVertexArray(m_VAO);
    }

    void Mesh::Unbind() const 
    {
        glBindVertexArray(0);
    }

    std::shared_ptr<Mesh> Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        if (indices.empty())
        {
            Logger::Log(LogLevel::Warning, "Attempted to create mesh with no indices.");
            return nullptr;
        }

        try 
        {
            return std::make_shared<Mesh>(vertices, indices);
        }
        catch (const std::exception& e) 
        {
            Logger::Log(LogLevel::Fatal, "Mesh creation failed: " + std::string(e.what()));
            return nullptr;
        }
    }

    void Mesh::Draw() const 
    {
        if (!m_Initialized || !m_VAO || !m_VBO || m_Indices.empty()) 
        {
            Logger::Log(LogLevel::Warning, "Draw skipped: mesh not initialized or missing data.");
            return;
        }

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    const Bounds& Mesh::GetBounds() const 
    {
        if (!m_BoundsDirty) return bounds;

        if (m_Vertices.empty()) 
        {
            bounds = Bounds(glm::vec3(0.0f), glm::vec3(0.0f));
            m_BoundsDirty = false;
            return bounds;
        }

        glm::vec3 minPos = m_Vertices[0].Position;
        glm::vec3 maxPos = m_Vertices[0].Position;

        for (const auto& v : m_Vertices)
        {
            minPos = glm::min(minPos, v.Position);
            maxPos = glm::max(maxPos, v.Position);
        }

        bounds = Bounds(minPos, maxPos);
        m_BoundsDirty = false;
        return bounds;
    }

    void Mesh::SetName(std::string name)
    {
        this->name = name;
    }

    bool Mesh::IsRenderable() const
    { 
        return m_Initialized && m_VAO && m_VBO && !m_Indices.empty();
    }
}