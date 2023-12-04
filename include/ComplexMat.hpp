#pragma once

#include <complex>

#include <opencv2/core.hpp>
#include <Eigen/Dense>

class ComplexMat
{
    public:
    ComplexMat(cv::Mat real, cv::Mat imag);

        std::complex<double> operator() (int i, int j);

        const cv::Mat& real();
        const cv::Mat& imag();

        int cols;
        int rows;

        ComplexMat operator* (std::complex<double> z);

        void mul(std::complex<double> z);

    private:
        cv::Mat m_real;
        cv::Mat m_imag;
};