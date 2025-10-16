#include "ImageEngine.h"

namespace Orca
{
	ImageEngine::ImageEngine() = default;
	ImageEngine::~ImageEngine() { Unload(); }

	bool ImageEngine::Load(const std::string& filePath)
	{
		Unload();
		m_Source = std::make_unique<ImageSource>(filePath);
		return m_Source->IsLoaded();
	}

	void ImageEngine::Unload()
	{
		m_Source.reset();
	}

	bool ImageEngine::IsLoaded() const
	{
		return m_Source && m_Source->IsLoaded();
	}

	const cv::Mat& ImageEngine::GetCurrentImage() const
	{
		static cv::Mat empty;
		return IsLoaded() ? m_Source->GetImage() : empty;
	}

	int ImageEngine::GetWidth() const
	{
		return IsLoaded() ? m_Source->GetWidth() : 0;
	}

	int ImageEngine::GetHeight() const
	{
		return IsLoaded() ? m_Source->GetHeight() : 0;
	}

	int ImageEngine::GetChannels() const
	{
		return IsLoaded() ? m_Source->GetChannels() : 0;
	}

	unsigned char* ImageEngine::GetPixelData() const
	{
		return IsLoaded() ? m_CurrentImage.data : nullptr;
	}

	int ImageEngine::GetStride() const
	{
		return IsLoaded() ? static_cast<int>(m_CurrentImage.step) : 0;
	}
}