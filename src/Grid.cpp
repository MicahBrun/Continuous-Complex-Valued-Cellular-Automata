#include "../include/Grid.hpp"
#include "../include/ComplexToColor.hpp"

#include <SFML/Graphics.hpp>
#include <Eigen/Dense>

#include <cmath>
#include <vector>

bool Grid::load(sf::Vector2f tileSize, unsigned int width, unsigned int height)
{
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j)
    {
        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
        quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
        quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
    }

    m_width = width;
    m_height = height;

    return true;
}

void Grid::setValues(const Eigen::MatrixXcd& values)
{
    auto plain = values.data();
    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < m_width; ++i)
    for (unsigned int j = 0; j < m_height; ++j)
    {
        int x = i + j * m_width;
        ComplexToColor::RGB rgb = ComplexToColor::complexToRGB(plain[x]);
        sf::Vertex* quad = &m_vertices[(x) * 4];

        for (int corner = 0; corner < 4; ++corner)
        {
            sf::Vertex& vertex = quad[corner];
            vertex.color.r = rgb.r;
            vertex.color.g = rgb.g;
            vertex.color.b = rgb.b;
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // draw the vertex array
    target.draw(m_vertices, states);
}