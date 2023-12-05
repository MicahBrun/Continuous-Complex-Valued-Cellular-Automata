#include "../include/Transforms.hpp"

#include <opencv2/core.hpp>

#include <vector>

namespace Transforms
{
    cv::Mat Convolve(cv::Mat& a, cv::Mat& kernel)
    {
        cv::Mat aTransformed;
        cv::dft(a, aTransformed);

        cv::Mat kernelTransformed;
        cv::dft(kernel, kernelTransformed);

        cv::Mat convolvedTransformed;
        cv::mulSpectrums(aTransformed, kernelTransformed, convolvedTransformed, 0);

        cv::Mat convolved;
        cv::idft(convolvedTransformed, convolved);

        return convolved;
    }

    cv::Mat applyStep(cv::Mat& space, cv::Mat& transformedKernel)
    {
        cv::Mat spaceTransformed;
        cv::dft(space, spaceTransformed);

        cv::Mat convolvedTransformed;
        cv::mulSpectrums(spaceTransformed, transformedKernel, convolvedTransformed, 0);

        cv::Mat convolved;
        cv::idft(convolvedTransformed, convolved);

        cv::Mat spaceOut {space + convolved};
        return clipMagnitude(spaceOut);
    }

    cv::Mat clipMagnitude(cv::Mat complexMat)
    {
        cv::Mat sources[2];
        cv::split(complexMat, sources);

        cv::Mat mag;
        cv::magnitude(sources[0], sources[1], mag);

        auto mask {mag <= 1};
        mag.setTo(1.0f, mask);

        cv::Mat outReal;
        cv::Mat outImag;
        cv::divide(sources[0], mag, outReal);
        cv::divide(sources[1], mag, outImag);

        cv::Mat out;
        cv::merge(std::vector<cv::Mat> {outReal, outImag}, out);
        return out;
    }
}

