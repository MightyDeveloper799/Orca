#include "AssetLoader.h"
#include "../Core/Logger.h"
#include <thread>
#include <algorithm>
#include <fstream>

namespace Orca
{
	AssetPtr AssetLoader::PerformLoad(const std::string& path)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);

		AssetPtr loadedAsset = std::make_shared<Asset>();
		if (!file.is_open())
		{
			Logger::Log(LogLevel::Error, "Failed to open the file: " + path);
			return loadedAsset;
		}

		size_t fileSize = (size_t)file.tellg();

		file.seekg(0, std::ios::beg);

		size_t lastSlash = path.find_last_of("/\\");
		loadedAsset->name = (lastSlash == std::string::npos)
			? path
			: path.substr(lastSlash + 1);

		loadedAsset->dataSize = fileSize;

		try
		{
			loadedAsset->rawData.resize(fileSize);

			file.read(loadedAsset->rawData.data(), fileSize);

			if (file.fail() && !file.eof())
			{
				Logger::Log(LogLevel::Error, "Failed to open the file: " + path);
				loadedAsset->isLoaded = false;
				loadedAsset->rawData.clear();
			}
			else
			{
				loadedAsset->isLoaded = true;
			}
		}

		catch (const std::exception& e)
		{
			Logger::Log(LogLevel::Error, std::string("Failed to read the file: " + path) + e.what());
			loadedAsset->isLoaded = false;
			loadedAsset->rawData.clear();
		}

		return loadedAsset;
	}

	std::future<AssetPtr> AssetLoader::LoadAsync(const std::string& path)
	{
		return std::async(std::launch::async, &AssetLoader::PerformLoad, this, path);
	}
}