#include "VideoSource.h"
#include <iostream>

namespace Orca
{
	VideoSource::VideoSource(const std::string& filePath)
		: m_Path(filePath), m_Capture(filePath)
	{
		if (!m_Capture.isOpened())
		{
			std::cerr << "[VideoSource] Failed to open" << filePath << std::endl;
		}
	}

	VideoSource::~VideoSource()
	{
		m_Capture.release();
	}

	bool VideoSource::IsOpen() const
	{
		return m_Capture.isOpened();
	}

	bool VideoSource::ReadFrames(cv::Mat& outFrame)
	{
		return m_Capture.read(outFrame);
	}

	double VideoSource::GetFPS() const
	{
		return m_Capture.get(cv::CAP_PROP_FPS);
	}

	int VideoSource::GetWidth() const
	{
		return static_cast<int>(m_Capture.get(cv::CAP_PROP_FRAME_WIDTH));
	}

	int VideoSource::GetHeight() const
	{
		return static_cast<int>(m_Capture.get(cv::CAP_PROP_FRAME_HEIGHT));
	}

	std::string VideoSource::GetPath() const
	{
		return m_Path;
	}
}