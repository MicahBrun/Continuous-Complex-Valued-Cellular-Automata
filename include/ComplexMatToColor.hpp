#pragma once

#include <opencv2/core.hpp>

namespace Color
{
    cv::Mat complexMatToRgb(const cv::Mat& mat, float saturation);
}