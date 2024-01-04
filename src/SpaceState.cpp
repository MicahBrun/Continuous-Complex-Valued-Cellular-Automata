#include "../include/SpaceState.hpp"
#include "../include/Transforms.hpp"

#include <Eigen/Core>
#include <opencv2/core.hpp>
#include <opencv2/core/eigen.hpp>

SpaceState::SpaceState(const cv::Mat& initialState, const cv::Mat& kernel, float deltaTime)
{
    initialState.copyTo(m_state);

    cv::dft(kernel, m_transformedKernel);
    Eigen::MatrixXcf eigenMat {Transforms::convertToEigenComplex(m_transformedKernel)};

    auto mapLambda = [&](std::complex<float> z) -> std::complex<float>
    {
        const std::complex<float> j {0.0, 1.0};
        return std::exp(-deltaTime * j * z);
    };
    eigenMat = eigenMat.unaryExpr(mapLambda);

    m_transformedKernel = Transforms::convertToOpenCV2Channel(eigenMat);
}

const cv::Mat& SpaceState::getState() const
{
    return m_state;
}

void SpaceState::evolve()
{
    auto curState {Transforms::applyStep(m_state, m_transformedKernel)};
    m_state = curState;
}