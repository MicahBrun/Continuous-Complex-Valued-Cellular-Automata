#include "../include/ComplexMatToColor.hpp"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <cmath>
#include <iostream>

namespace ComplexMatToColor
{
    cv::Mat complexMatToRgb(cv::Mat& mat)
    {
        cv::Mat channels[2];
        cv::split(mat, channels);

        cv::Mat magnitudeMat;
        cv::magnitude(channels[0], channels[1], magnitudeMat);

        cv::Mat phaseMat;
        cv::phase(channels[0], channels[1], phaseMat, true);

        const double k {1.0};
        const double s {1.15051};

        auto mapLambda = [&](double &f, const int *p) -> void
        {
            if (f < k)
            {
                f = f / s;
                return;
            }
            f = (k + std::fmod(f - k, s - k)) / s;
        };
        magnitudeMat.forEach<double>(mapLambda);

        cv::Mat hueMat {phaseMat};

        cv::Mat satMat {cv::Mat::ones(magnitudeMat.size(), magnitudeMat.type())};
        cv::Mat hsvMat;

        cv::merge(std::vector<cv::Mat> {hueMat, satMat, magnitudeMat}, hsvMat);
        hsvMat.convertTo(hsvMat, CV_32F);

        cv::Mat rgbMat;
        cv::cvtColor(hsvMat, rgbMat, cv::COLOR_HSV2RGB);
        return rgbMat;
    }
}