#pragma once

#ifndef ANIMATION_IMPORTER_H
#define ANIMATION_IMPORTER_H

#include <iostream>
#include "OrcaAPI.h"
#include "AnimationClip.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API AnimationImporter
	{
	public:
		static std::vector<AnimationClip> ImportFromGLB(const std::string& filePath);
	};
#pragma warning(pop)
}

#endif