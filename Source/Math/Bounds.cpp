#include "Bounds.h"
#include <algorithm>

namespace Orca {

    Bounds::Bounds()
        : m_Min(glm::vec3(0.0f)), m_Max(glm::vec3(0.0f)) { }

    Bounds::Bounds(Vertex min, Vertex max) : min(min), max(max) {}

    Bounds::Bounds(const glm::vec3& min, const glm::vec3& max)
        : m_Min(min), m_Max(max) { }

    void Bounds::Expand(const glm::vec3& point) 
    {
        m_Min = glm::min(m_Min, point);
        m_Max = glm::max(m_Max, point);
    }

    bool Bounds::Contains(const glm::vec3& point) const 
    {
        return glm::all(glm::greaterThanEqual(point, m_Min)) &&
            glm::all(glm::lessThanEqual(point, m_Max));
    }

    bool Bounds::Intersects(const Bounds& other) const 
    {
        return (m_Min.x <= other.m_Max.x && m_Max.x >= other.m_Min.x) &&
            (m_Min.y <= other.m_Max.y && m_Max.y >= other.m_Min.y) &&
            (m_Min.z <= other.m_Max.z && m_Max.z >= other.m_Min.z);
    }

    glm::vec3 Bounds::GetCenter() const 
    {
        return (m_Min + m_Max) * 0.5f;
    }

    glm::vec3 Bounds::GetSize() const 
    {
        return m_Max - m_Min;
    }

    const glm::vec3& Bounds::GetMin() const 
    {
        return m_Min;
    }

    const glm::vec3& Bounds::GetMax() const 
    {
        return m_Max;
    }
}