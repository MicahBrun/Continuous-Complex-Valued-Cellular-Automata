#pragma once

#include <SFML/Graphics.hpp>
#include <Eigen/Dense>

#include <complex>

class Grid : public sf::Drawable, public sf::Transformable
{
public:

    bool load(sf::Vector2f tileSize, unsigned int width, unsigned int height);

    void setValues(const Eigen::MatrixXcd& values);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;

    int m_width;
    int m_height;
};