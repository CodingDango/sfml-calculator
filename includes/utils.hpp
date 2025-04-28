#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

namespace utils
{
    sf::Texture loadTexture(const std::string& path);

    sf::Color modifyColorByFactor(sf::Color color, float factor);

    sf::Font loadFont(const std::string& path);
}