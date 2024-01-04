#include "../include/Grid.hpp"
#include "../include/ComplexMatToColor.hpp"
#include "../include/SpaceState.hpp"
#include "../include/Transforms.hpp"
#include "../include/main.hpp"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <opencv2/core.hpp>

int main()
{
    int rows {1024};
    int cols {1024};

    float colorSaturation {0.15f};

    cv::Mat kernel {createKernel(rows, cols, 40)};
    cv::Mat initialState {createInitialState(rows, cols, 40)};
    
    float deltaTime {0.01f};
    SpaceState state {initialState, kernel, deltaTime};

    sf::Vector2f tileSize {0.5, 0.5};

    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode((int)(tileSize.x * rows), (int)(tileSize.y * cols)), "SFML Matrix Display");

    Grid grid {};
    grid.load(sf::Vector2f{0.5, 0.5}, rows, cols, colorSaturation);
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

        state.evolve();

    }

    return 0;
}

cv::Mat createKernel(int rows, int cols, float scale)
{
    cv::Mat kernelReal = cv::Mat::zeros(rows, cols, CV_32F);
    cv::Mat kernelImag = cv::Mat::zeros(rows, cols, CV_32F);

    for (int i = 0; i < kernelReal.rows; i++)
    for (int j = 0; j < kernelReal.cols; j++)
    {
        double x {(((i + rows/2) % rows) - rows/2) / scale};
        double y {(((j + cols/2) % cols) - cols/2) / scale};

        std::complex<float>z(x, y);
        float lambda { 0.5f };
        float kappa { 1.0f };

        auto w { std::pow(std::sin(std::abs(z)/500), 2)/30.0 * std::exp(-std::norm(z)/(lambda * lambda)) / kappa}; 
        kernelReal.at<float>(i, j) = std::real(w);
        kernelImag.at<float>(i, j) = std::imag(w);
    }

    cv::Mat kernel;
    cv::merge(std::vector<cv::Mat>{kernelReal, kernelImag}, kernel);
    kernel /= Transforms::getNorm(kernel);

    return kernel;
}

cv::Mat createInitialState(int rows, int cols, float scale)
{
    cv::Mat initialStateReal = cv::Mat::zeros(rows, cols, CV_32F);
    cv::Mat initialStateImag = cv::Mat::zeros(rows, cols, CV_32F);

    for (int i = 0; i < initialStateReal.rows; ++i)
    for (int j = 0; j < initialStateReal.cols; ++j)
    {
        float radius {2};

        std::complex<float> z {((float)i - rows/2)/scale, (float)(j - cols/2)/scale};
        std::complex<float> w {z * (std::exp(-std::norm(z)/(radius * radius)) + std::exp(-std::norm(z - 2.0f * radius)/(radius * radius)))};
        initialStateReal.at<float>(i, j) = w.real();
        initialStateImag.at<float>(i, j) = w.imag();
    }
    
    cv::Mat initialState;
    cv::merge(std::vector<cv::Mat> {initialStateReal, initialStateImag}, initialState);

    return initialState;
}