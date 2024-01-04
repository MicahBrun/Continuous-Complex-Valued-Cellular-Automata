#include "../include/Grid.hpp"
#include "../include/ComplexMatToColor.hpp"
#include "../include/SpaceState.hpp"
#include "../include/Transforms.hpp"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <opencv2/core.hpp>

int main()
{
    cv::Mat kernelReal = cv::Mat::zeros(1024, 1024, CV_32F);
    cv::Mat kernelImag = cv::Mat::zeros(1024, 1024, CV_32F);

    float scale {50.0f};
    for (int i = 0; i < kernelReal.rows; i++)
    {
      for (int j = 0; j < kernelReal.cols; j++)
      {
        double x {(((i + 512) % 1024) - 512) / scale};
        double y {(((j + 512) % 1024) - 512) / scale};

        std::complex<float>z(x, y);
        float lambda { 8.0f };
        float kappa { 1.0f };
        //std::complex<float> w {0};
        auto w { std::norm(z)/30.0 * std::exp(-std::norm(z)/(lambda * lambda)) / kappa}; 
        kernelReal.at<float>(i, j) = std::real(w);
        kernelImag.at<float>(i, j) = std::imag(w);
      }
    }

    cv::Mat kernel;
    cv::merge(std::vector<cv::Mat>{kernelReal, kernelImag}, kernel);
    kernel /= Transforms::getNorm(kernel);

    cv::Mat initialStateReal = cv::Mat::zeros(kernel.size(), CV_32F);
    cv::Mat initialStateImag = cv::Mat::zeros(kernel.size(), CV_32F);

    cv::Mat lReal = cv::Mat::zeros(kernel.size(), CV_32F);
    cv::Mat lImag = cv::Mat::zeros(kernel.size(), CV_32F);

    cv::randn(lReal, cv::Scalar(0), cv::Scalar(10));
    cv::randn(lImag, cv::Scalar(0), cv::Scalar(10));

    initialStateReal = initialStateReal.mul(kernelReal);
    initialStateImag = initialStateImag.mul(kernelReal);

    for (int i = 0; i < initialStateReal.rows; ++i)
    for (int j = 0; j < initialStateReal.cols; ++j)
    {
        std::complex<float> z {(float)std::sin((i - 512.0)*M_PI/512.0), (float)std::sin((j - 512.0)*M_PI/512.0)};
        std::complex<float> w {2.0f * z * std::exp(-std::norm(z)) / 1.0f};
        initialStateReal.at<float>(i, j) = w.real();
        initialStateImag.at<float>(i, j) = w.imag();
    }

    initialStateReal = initialStateReal;// + 0.1 * lReal;
    initialStateImag = initialStateImag;// + 0.1 * lImag;
    
    cv::Mat initialState;
    cv::merge(std::vector<cv::Mat> {initialStateReal, initialStateImag}, initialState);

    SpaceState state {initialState, kernel};
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Matrix Display");

    Grid grid {};
    grid.load(sf::Vector2f{0.5, 0.5}, 1024, 1024);
    // Main loop
    while (window.isOpen()) 
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }
        // Clear the window
        window.clear();

        grid.setValues(state.getState());
        window.draw(grid);

        // Display the window
        window.display();

        state.evolve(0.1);

    }

    return 0;
}