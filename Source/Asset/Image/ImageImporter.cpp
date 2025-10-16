#include "ImageImporter.h"
#include "ImageSource.h"
#include <filesystem>

namespace Orca 
{
    std::vector<ImageMetadata> ImageImporter::ImportFolder(const std::string& folderPath) 
    {
        std::vector<ImageMetadata> results;
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) 
        {
            if (entry.is_regular_file()) 
            {
                std::string path = entry.path().string();
                ImageSource source(path);
                if (source.IsLoaded()) 
                {
                    results.push_back(source.GetMetadata());
                }
            }
        }

        return results;
    }
}