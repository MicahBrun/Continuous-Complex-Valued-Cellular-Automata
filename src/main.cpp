#include "../include/Grid.hpp"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

int main()
{
    Eigen::MatrixXcd matrix(500, 500);
    double scale {50.0};
    for (int i = 0; i < matrix.rows(); i++)
    {
      for (int j = 0; j < matrix.cols(); j++)
      {
        double x {(i - 250.0) / scale};
        double y {(j - 250.0) / scale};

        std::complex<double>z(x, y);
        double lambda { 0.8 };
        double kappa { 15'000.0 };
        auto w { z*z/std::abs(z) /* std::exp(-std::norm(z)/(lambda * lambda))*/ }; //2.0 * z * std::exp(-std::norm(z / lambda)) / 100.0 };
        matrix(i, j) = w;
      }
    }

    const auto factor {1.01 * std::complex(1.0, 0.05)};
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(matrix.cols(), matrix.rows()), "SFML Matrix Display");

    Grid grid {};
    grid.load(sf::Vector2f{1.0, 1.0}, 500, 500);
    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();

        matrix *= factor;
        grid.setValues(matrix);
        window.draw(grid);

        // Display the window
        window.display();
        sf::sleep(sf::milliseconds(500));
    }

    return 0;
}