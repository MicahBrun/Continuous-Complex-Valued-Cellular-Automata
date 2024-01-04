#pragma once

#include <opencv2/core.hpp>
#include <Eigen/Core>
#include <opencv2/core.hpp>
#include <opencv2/core/eigen.hpp>

namespace Transforms
{
    cv::Mat Convolve(cv::Mat& a, cv::Mat& kernel);

    cv::Mat applyStep(cv::Mat& space, cv::Mat& transformedKernel);

    cv::Mat clipMagnitude(cv::Mat complexMat);

    cv::Mat iMul(cv::Mat& mat);

    float getNorm(const cv::Mat&);

    Eigen::MatrixXcf convertToEigenComplex(const cv::Mat& inputMat); 

    cv::Mat convertToOpenCV2Channel(const Eigen::MatrixXcf& eigenComplex);
}

