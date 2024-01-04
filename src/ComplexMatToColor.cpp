#include "../include/ComplexMatToColor.hpp"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <cmath>
#include <iostream>

namespace Color
{
    cv::Mat complexMatToRgb(const cv::Mat& mat, float saturation)
    {
        cv::Mat channels[2];
        cv::split(mat, channels);

        cv::Mat magnitudeMat;
        cv::magnitude(channels[0], channels[1], magnitudeMat);

        cv::Mat phaseMat;
        cv::phase(channels[0], channels[1], phaseMat, true);

        const float k {1.0f};
        const float s {1.15051f};

        auto mapLambda = [&](float &f, const int *p) -> void
        {
            f = std::atan(f * f) * (2.0f / M_PI);
        };
        magnitudeMat.forEach<float>(mapLambda);

        cv::Mat hueMat {phaseMat};

        cv::Mat satMat {saturation * cv::Mat::ones(magnitudeMat.size(), magnitudeMat.type())};
        cv::Mat hsvMat;

        cv::merge(std::vector<cv::Mat> {hueMat, satMat, magnitudeMat}, hsvMat);
        hsvMat.convertTo(hsvMat, CV_32F);

        cv::Mat rgbMat;
        cv::cvtColor(hsvMat, rgbMat, cv::COLOR_HSV2RGB);
        return rgbMat;
    }
}