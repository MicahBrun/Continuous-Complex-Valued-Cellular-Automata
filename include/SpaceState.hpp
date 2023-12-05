#pragma once

#include <opencv2/core.hpp>

class SpaceState
{
    public:
        SpaceState(const cv::Mat& initialState, const cv::Mat& kernel);

        const cv::Mat& getState() const;
        void evolve(float deltaTime);
    
    private:
        cv::Mat m_state;
        cv::Mat m_transformedKernel;
};