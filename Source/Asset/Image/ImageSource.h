#pragma once

#ifndef IMAGE_SOURCE_H
#define IMAGE_SOURCE_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "ImageMetadata.h"
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API ImageSource
	{
	public:
		explicit ImageSource(const std::string& filePath);
		ImageSource(const std::string& filePath, bool deferLoad);
		~ImageSource();

		bool IsLoaded() const;
		const cv::Mat& GetImage() const;

		void Load();

		int GetWidth() const;
		int GetHeight() const;
		int GetChannels() const;
		std::string GetPath() const;
		std::vector<cv::Mat> GenerateMipmaps(const cv::Mat& base, int level);

		ImageMetadata GetMetadata() const;
	private:
		cv::Mat m_Image;
		std::string m_Path;
	};

#pragma warning(pop)
}

#endif