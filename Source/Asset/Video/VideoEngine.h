#pragma once

#ifndef VIDEO_ENGINE_H
#define VIDEO_ENGINE_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "VideoSource.h"
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API VideoEngine
	{
	public:
		VideoEngine();
		~VideoEngine();

		bool Load(const std::string& filePath);
		bool Update();
		const cv::Mat& GetCurrentFrame() const;
		void Unload();

		bool IsLoaded() const;
		double GetFPS() const;
		int GetWidth() const;
		int GetHeight() const;
	private:
		std::unique_ptr<VideoSource> m_Source;
		cv::Mat m_CurrentFrame;
	};
#pragma warning(pop)
}

#endif