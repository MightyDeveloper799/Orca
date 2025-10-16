#include "ImageSource.h"
#include <iostream>

namespace Orca
{
	ImageSource::ImageSource(const std::string& filePath)
		: m_Path(filePath)
	{
		m_Image = cv::imread(filePath, cv::IMREAD_UNCHANGED);
		if (m_Image.empty())
		{
			std::cerr << "[ImageSource] Failed to open" << filePath << std::endl;
		}
	}

	ImageSource::ImageSource(const std::string& filePath, bool deferLoad)
		: m_Path(filePath)
	{
		if (!deferLoad)
		{
			m_Image = cv::imread(filePath, cv::IMREAD_UNCHANGED);
		}
	}

	ImageSource::~ImageSource()
	{
		m_Image.release();
	}

	bool ImageSource::IsLoaded() const
	{
		return !m_Image.empty();
	}

	const cv::Mat& ImageSource::GetImage() const
	{
		return m_Image;
	}

	void ImageSource::Load()
	{
		if (m_Image.empty())
		{
			m_Image = cv::imread(m_Path, cv::IMREAD_UNCHANGED);
		}
	}

	int ImageSource::GetWidth() const
	{
		return m_Image.cols;
	}

	int ImageSource::GetHeight() const
	{
		return m_Image.rows;
	}

	int ImageSource::GetChannels() const
	{
		return m_Image.channels();
	}

	std::string ImageSource::GetPath() const
	{
		return m_Path;
	}

	std::vector<cv::Mat> ImageSource::GenerateMipmaps(const cv::Mat& base, int levels)
	{
		std::vector<cv::Mat> mipmaps;
		mipmaps.push_back(base.clone());
		for (int i = 1; i < levels; ++i) 
		{
			cv::Mat down;
			cv::pyrDown(mipmaps.back(), down);
			mipmaps.push_back(down);
		}
		return mipmaps;
	}

	ImageMetadata ImageSource::GetMetadata() const
	{
		ImageMetadata meta;
		meta.path = m_Path;
		meta.width = GetWidth();
		meta.height = GetHeight();
		meta.channels = GetChannels();
		meta.hasAlpha = (meta.channels == 4);
		return meta;
	}
}