#include "../include/SpaceState.hpp"
#include "../include/Transforms.hpp"

#include <opencv2/core.hpp>

SpaceState::SpaceState(const cv::Mat& initialState, const cv::Mat& kernel)
{
    initialState.copyTo(m_state);

    cv::dft(kernel, m_transformedKernel);
};

const cv::Mat& SpaceState::getState() const
{
    return m_state;
}

void SpaceState::evolve(float deltaTime)
{
    m_state = Transforms::applyStep(m_state, m_transformedKernel);
}
