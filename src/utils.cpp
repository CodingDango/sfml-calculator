#include "utils.hpp"

//===============================================================
// namespace utils function definitions
//===============================================================
 
sf::Texture utils::loadTexture(const std::string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

sf::Color utils::modifyColorByFactor(sf::Color color, float factor)
{
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
    return color;
}

sf::Font utils::loadFont(const std::string& path)
{
    sf::Font font {};
    if (!font.loadFromFile(path))
        std::cerr << "Font with path '" << path << "' could not be loaded.\n";
    return font;
}

sf::Color utils::modifyColorOpacity(sf::Color color, double value)
{
    color.a = std::min<int>(255, std::max<int>(0, value));
    return color;
}