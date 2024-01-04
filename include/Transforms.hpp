#pragma once

#include <opencv2/core.hpp>

namespace Transforms
{
    cv::Mat Convolve(cv::Mat& a, cv::Mat& kernel);

    cv::Mat applyStep(cv::Mat& space, cv::Mat& transformedKernel);

    cv::Mat clipMagnitude(cv::Mat complexMat);

    cv::Mat iMul(cv::Mat& mat);

    float getNorm(const cv::Mat&);
}

