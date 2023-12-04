#include "../include/ComplexMat.hpp"

#include <complex>

#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

ComplexMat::ComplexMat(cv::Mat real, cv::Mat imag)
{
    m_real = std::move(real);
    m_imag = std::move(imag);

    rows = m_real.rows;
    cols = m_real.cols;
}

std::complex<double> ComplexMat::operator() (int i, int j)
{
    return std::complex(m_real.at<double>(i, j), m_imag.at<double>(i, j));
}



ComplexMat ComplexMat::operator*(std::complex<double> z)
{
    auto real {std::real(z) * m_real - std::imag(z) * m_imag};
    auto imag {std::imag(z) * m_real + std::real(z) * m_imag};

    return ComplexMat 
    {
        cv::Mat1d(real), 
        cv::Mat1d(imag),
    };
}

void ComplexMat::mul(std::complex<double> zr)
{
    for (int i {0}; i < m_real.cols; i++)
    for (int j {0}; j < m_real.rows; j++)
    {
        auto zl = std::complex(m_real.at<double>(i, j), m_imag.at<double>(i, j));
        auto zout = zl * zr;
        m_real.at<double>(i, j) = std::real(zout);
        m_imag.at<double>(i, j) = std::imag(zout);
    }
}

const cv::Mat& ComplexMat::real() 
{
    return m_real;
}

const cv::Mat& ComplexMat::imag() 
{
    return m_imag;
}