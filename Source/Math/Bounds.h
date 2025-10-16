#pragma once

#ifndef BOUNDS_H
#define BOUNDS_H

#include "../Renderer/Vertex.h"
#include "../OrcaAPI.h"
#include <glm/glm.hpp>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API Bounds
	{
    public:
        Bounds();
        Bounds(Vertex min, Vertex max);
        Bounds(const glm::vec3& min, const glm::vec3& max);

        void Expand(const glm::vec3& point);
        bool Contains(const glm::vec3& point) const;
        bool Intersects(const Bounds& other) const;

        glm::vec3 GetCenter() const;
        glm::vec3 GetSize() const;

        const glm::vec3& GetMin() const;
        const glm::vec3& GetMax() const;

    private:
        glm::vec3 m_Min;
        glm::vec3 m_Max;

        Vertex min; 
        Vertex max;
	};
}

#endif