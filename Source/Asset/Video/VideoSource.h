#pragma once

#ifndef VIDEO_SOURCE_H
#define VIDEO_SOURCE_H

#include <string>
#include <opencv2/opencv.hpp>
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API VideoSource
	{
	public:
		explicit VideoSource(const std::string& filePath);
		~VideoSource();

		bool IsOpen() const;
		bool ReadFrames(cv::Mat& outFrame);
		void Reset();

		double GetFPS() const;
		int GetWidth() const;
		int GetHeight() const;
		std::string GetPath() const;
	private:
		cv::VideoCapture m_Capture;
		std::string m_Path;
	};
#pragma warning(pop)
}

#endif