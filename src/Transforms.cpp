#include "../include/Transforms.hpp"

#include <opencv2/core.hpp>
#include <Eigen/Core>
#include <opencv2/core.hpp>
#include <opencv2/core/eigen.hpp>

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
        cv::dft(space, spaceTransformed, cv::DFT_SCALE);

        cv::Mat convolvedTransformed;
        cv::mulSpectrums(spaceTransformed, transformedKernel, convolvedTransformed, 0);

        cv::Mat convolved;
        cv::idft(convolvedTransformed, convolved);

        return convolved;
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

    cv::Mat iMul(cv::Mat& mat)
    {
        cv::Mat sources[2];
        cv::split(mat, sources);
        
        cv::Mat iMat;
        cv::merge(std::vector<cv::Mat>{-sources[1], sources[0]}, iMat);

        return iMat;
    }

    float getNorm(const cv::Mat& mat)
    {
        cv::Mat sources[2];
        cv::split(mat, sources);

        cv::Mat mag;
        cv::magnitude(sources[0], sources[1], mag);
        return std::sqrt(cv::sum(mat.mul(mat))[0]);
    }

    Eigen::MatrixXcf convertToEigenComplex(const cv::Mat& inputMat) 
    {
        std::vector<cv::Mat> channels;
        cv::split(inputMat, channels);

        cv::Mat realPart = channels[0];
        cv::Mat imagPart = channels[1];

        Eigen::MatrixXf eigenReal;
        cv::cv2eigen(realPart, eigenReal);
        Eigen::MatrixXf eigenImag;
        cv::cv2eigen(imagPart, eigenImag);

        Eigen::MatrixXcf complexMatrix(eigenReal.rows(), eigenReal.cols());
        complexMatrix.real() = eigenReal;
        complexMatrix.imag() = eigenImag;

        return complexMatrix;
    }

    cv::Mat convertToOpenCV2Channel(const Eigen::MatrixXcf& eigenComplex) 
    {
        cv::Mat opencvMatrix(eigenComplex.rows(), eigenComplex.cols(), CV_32FC2);

        Eigen::MatrixXf real {eigenComplex.real()};
        Eigen::MatrixXf imag {eigenComplex.imag()};

        cv::Mat cvReal {};
        cv::eigen2cv(real, cvReal);

        cv::Mat cvImag {};
        cv::eigen2cv(imag, cvImag);

        cv::Mat out;
        cv::merge(std::vector<cv::Mat>{cvReal, cvImag}, out);

        return out;
    }
}

