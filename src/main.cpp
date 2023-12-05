#include "../include/Grid.hpp"
#include "../include/ComplexMatToColor.hpp"
#include "../include/SpaceState.hpp"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <opencv2/core.hpp>

int main()
{
    cv::Mat kernelReal = cv::Mat::zeros(2000, 2000, CV_32F);
    cv::Mat kernelImag = cv::Mat::zeros(2000, 2000, CV_32F);

    float scale {1.0f};
    for (int i = 0; i < kernelReal.rows; i++)
    {
      for (int j = 0; j < kernelReal.cols; j++)
      {
        double x {(((i + 1000) % 2000) - 1000) / scale};
        double y {(((j + 1000) % 2000) - 1000) / scale};

        std::complex<float>z(x, y);
        float lambda { 10.0f };
        float kappa { 250.0f };
        auto w { (std::complex<float>(1, 0.01) + 0.000001f * (z/std::abs(z))) * std::exp(-std::norm(z)/(lambda * lambda)) / kappa}; 
        kernelReal.at<float>(i, j) = std::real(w);
        kernelImag.at<float>(i, j) = std::imag(w);
      }
    }

    cv::Mat kernel;
    cv::merge(std::vector<cv::Mat>{kernelReal, kernelImag}, kernel);

    cv::Mat initialStateReal = cv::Mat::zeros(kernel.size(), CV_32F);
    cv::Mat initialStateImag = cv::Mat::zeros(kernel.size(), CV_32F);
    // Set values to 1 where x-axis is greater than 100
    for (int i = 0; i < initialStateReal.rows; ++i) {
        for (int j = 0; j < initialStateReal.cols; ++j) {
            if (j >= 1000) {
                std::complex<float> z {std::exp(std::complex<float>(0, i * (M_PI / 500.0f)))};
                initialStateReal.at<float>(i, j) = z.real();
                initialStateImag.at<float>(i, j) = z.imag();
            }
        }
    }

    cv::Mat initialState;
    cv::merge(std::vector<cv::Mat> {initialStateReal, initialStateImag}, initialState);

    SpaceState state {initialState, kernel};

    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "SFML Matrix Display");

    Grid grid {};
    grid.load(sf::Vector2f{1.0, 1.0}, 2000, 2000);
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
        state.evolve(0.00000001);

        window.draw(grid);

        // Display the window
        window.display();
    }

    return 0;
}