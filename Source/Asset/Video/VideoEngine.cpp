#include "VideoEngine.h"
#include <iostream>

namespace Orca
{
	VideoEngine::VideoEngine() = default;
	VideoEngine::~VideoEngine() { Unload(); }

	bool VideoEngine::Load(const std::string& filePath)
	{
		Unload();
		m_Source = std::make_unique<VideoSource>(filePath);
		return m_Source->IsOpen();
	}

	bool VideoEngine::Update()
	{
		if (!m_Source || !m_Source->IsOpen()) return false;
		return m_Source->ReadFrames(m_CurrentFrame);
	}

	const cv::Mat& VideoEngine::GetCurrentFrame() const
	{
		return m_CurrentFrame;
	}

	void VideoEngine::Unload()
	{
		m_Source.reset();
		m_CurrentFrame.release();
	}

	bool VideoEngine::IsLoaded() const
	{
		return m_Source && m_Source->IsOpen();
	}

	double VideoEngine::GetFPS() const
	{
		return m_Source ? m_Source->GetFPS() : 0.0;
	}

	int VideoEngine::GetWidth() const
	{
		return m_Source ? m_Source->GetWidth() : 0;
	}

	int VideoEngine::GetHeight() const
	{
		return m_Source ? m_Source->GetHeight() : 0;
	}
}