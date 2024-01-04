#pragma once

#include <Eigen/Core>
#include <opencv2/core.hpp>

class SpaceState
{
    public:
        SpaceState(const cv::Mat& initialState, const cv::Mat& kernel);

        const cv::Mat& getState() const;
        void evolve(float deltaTime);
    
    private:
        Eigen::MatrixXcf convertToEigenComplex(const cv::Mat& opencvMatrix);
        cv::Mat convertToOpenCV2Channel(const Eigen::MatrixXcf& eigenComplex);
        cv::Mat m_state;
        cv::Mat m_transformedKernel;
        float m_norm;
};