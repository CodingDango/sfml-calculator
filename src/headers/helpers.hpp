#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "entities.hpp"

namespace helpers 
{
    sf::Texture loadTextureFromFile(const std::string& path);

    void prepareButtons(ButtonContainer& container);

    sf::Color modifyColorByFactor(sf::Color color, float factor);
}