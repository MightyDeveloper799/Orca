#pragma once

#ifndef IMAGE_METADATA_H
#define IMAGE_METADATA_H

#include <string>
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	struct ORCA_API ImageMetadata
	{
		std::string path;
		int width = 0, height = 0, channels = 0;
		bool hasAlpha = false;
	};
#pragma warning(pop)
}

#endif