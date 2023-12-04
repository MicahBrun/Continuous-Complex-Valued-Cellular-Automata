#include "../include/Grid.hpp"
#include "../include/ComplexMatToColor.hpp"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <opencv2/core.hpp>

int main()
{
    cv::Mat1d matrixReal(2000, 2000);
    cv::Mat1d matrixImag(2000, 2000);

    double scale {1.0};
    for (int i = 0; i < matrixReal.rows; i++)
    {
      for (int j = 0; j < matrixReal.cols; j++)
      {
        double x {(i - 250.0) / scale};
        double y {(j - 250.0) / scale};

        std::complex<double>z(x, y);
        double lambda { 0.8 };
        double kappa { 25.0 };
        auto w { std::sqrt(z) * std::cos(std::log(std::norm(z)) + 0.5 * std::arg(z)) / kappa /* std::exp(-std::norm(z)/(lambda * lambda))*/ }; //2.0 * z * std::exp(-std::norm(z / lambda)) / 100.0 };
        matrixReal(i, j) = std::real(w);
        matrixImag(i, j) = std::imag(w);
      }
    }

    cv::Mat matrix;
    cv::merge(std::vector<cv::Mat>{matrixReal, matrixImag}, matrix);

    const auto factor {std::complex(1.0f, 0.02f)};
    auto matReal {factor.real() * cv::Mat::ones(matrix.size(), CV_32F)};
    auto matImag {factor.imag() * cv::Mat::ones(matrix.size(), CV_32F)};
    cv::Mat matFactor;
    cv::merge(std::vector<cv::Mat> {matReal, matImag}, matFactor);

    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Matrix Display");

    Grid grid {};
    grid.load(sf::Vector2f{1.0, 1.0}, 500, 500);
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

        grid.setValues(matrix);

        cv::Mat out[2];
        cv::split(matrix, out);
        std::vector<cv::Mat> out2 = 
        { 
          factor.real() * out[0] - factor.imag() * out[1], 
          factor.real() * out[1] + factor.imag() * out[0],
        };
        cv::merge(out2, matrix);

        window.draw(grid);

        // Display the window
        window.display();
    }

    return 0;
}