#pragma once

#ifndef IMAGE_ENGINE_H
#define IMAGE_DEFINE_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "ImageSource.h"
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API ImageEngine
    {
    public:
        ImageEngine();
        ~ImageEngine();

        bool Load(const std::string& filepath);
        void Unload();

        bool IsLoaded() const;
        const cv::Mat& GetCurrentImage() const;

        int GetWidth() const;
        int GetHeight() const;
        int GetChannels() const;

        unsigned char* GetPixelData() const;
        int GetStride() const;

    private:
        std::unique_ptr<ImageSource> m_Source;
        cv::Mat m_CurrentImage;
    };
#pragma warning(pop)
}

#endif