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

std::string utils::format_number(const std::string& str)
{
    // Can't be comma seperated
    if (str.size() <= 3)
        return str;
    
    std::string formatted {};

    int counter = 0;
    for (int i = str.size() - 1; i > -1; i--)
    {
        if (counter++ != 0 && counter % 3 == 0 && i != 0)
        {
            formatted += str[i];
            formatted += ',';
        }
        else
            formatted += str[i];
    }

    std::string reversed;

    for (int i = formatted.size() - 1; i > -1; i--)
        reversed += formatted[i];
        
    return reversed;
}