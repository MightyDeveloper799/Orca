#pragma once

#ifndef IMAGE_IMPORTER_H
#define IMAGE_IMPORTER_H

#include <vector>
#include <string>
#include "ImageMetadata.h"
#include "OrcaAPI.h"

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API ImageImporter
    {
    public:
        static std::vector<ImageMetadata> ImportFolder(const std::string& folderPath);
    };
#pragma warning(pop)
}

#endif