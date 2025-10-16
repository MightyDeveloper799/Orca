#pragma once

#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include <string>
#include "Model.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API ModelImporter
	{
	public:
		static Model ImportFromOBJ(const std::string& filePath);
		static Model ImportFromGLB(const std::string& filePath);
		static Model ImportFromGLTF(const std::string& filePath);
	};
#pragma warning(pop)
}

#endif