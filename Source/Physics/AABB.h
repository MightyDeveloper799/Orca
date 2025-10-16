#pragma once

#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	struct ORCA_API AABB
	{
		glm::vec3 min, max;

		bool Intersects(const AABB& other) const;
		bool Contains(const glm::vec3& point) const;
	};
#pragma warning(pop)
}

#endif