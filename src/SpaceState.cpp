#include "../include/SpaceState.hpp"
#include "../include/Transforms.hpp"

#include <Eigen/Core>
#include <opencv2/core.hpp>
#include <opencv2/core/eigen.hpp>

#include <iostream>

SpaceState::SpaceState(const cv::Mat& initialState, const cv::Mat& kernel)
{
    initialState.copyTo(m_state);

    cv::dft(kernel, m_transformedKernel);
    Eigen::MatrixXcf eigenMat {convertToEigenComplex(m_transformedKernel)};

    auto mapLambda = [](std::complex<float> z) -> std::complex<float>
    {
        const std::complex<float> j {0.0, 1.0};
        return std::exp(-0.002f * j * z);
    };
    eigenMat = eigenMat.unaryExpr(mapLambda);

    m_transformedKernel = convertToOpenCV2Channel(eigenMat);
}

const cv::Mat& SpaceState::getState() const
{
    return m_state;
}

void SpaceState::evolve(float deltaTime)
{
    auto curState {Transforms::applyStep(m_state, m_transformedKernel)};
    m_state = curState;
}

Eigen::MatrixXcf SpaceState::convertToEigenComplex(const cv::Mat& inputMat) 
{
    std::vector<cv::Mat> channels;
    cv::split(inputMat, channels);

    // Extract real and imaginary parts
    cv::Mat realPart = channels[0];
    cv::Mat imagPart = channels[1];

    // Create Eigen matrices from OpenCV matrices
    Eigen::MatrixXf eigenReal;
    cv::cv2eigen(realPart, eigenReal);
    Eigen::MatrixXf eigenImag;
    cv::cv2eigen(imagPart, eigenImag);

    // Create complex matrix using Eigen
    Eigen::MatrixXcf complexMatrix(eigenReal.rows(), eigenReal.cols());
    complexMatrix.real() = eigenReal;
    complexMatrix.imag() = eigenImag;

    return complexMatrix;
}

cv::Mat SpaceState::convertToOpenCV2Channel(const Eigen::MatrixXcf& eigenComplex) 
{
    // Create OpenCV 2-channel matrix with the same size as the Eigen matrix
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
