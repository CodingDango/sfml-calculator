#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>

namespace utils
{
    sf::Texture loadTexture(const std::string& path);
    sf::Color modifyColorByFactor(sf::Color color, float factor);
    sf::Font loadFont(const std::string& path);
    sf::Color modifyColorOpacity(sf::Color color, double value);
    std::string format_number(const std::string& str);
}

#endif