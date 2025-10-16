#pragma once

#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include <string>
#include <memory>
#include <future>
#include <chrono>
#include <vector>
#include <fstream>

namespace Orca
{
	struct Asset
	{
		std::string name;
		size_t dataSize = 0;
		bool isLoaded = false;
		std::vector<char> rawData;
	};

	using AssetPtr = std::shared_ptr<Asset>;

	class AssetLoader
	{
	public:
		std::future<AssetPtr> LoadAsync(const std::string& path);
	private:
		AssetPtr PerformLoad(const std::string& path);
	};
}

#endif