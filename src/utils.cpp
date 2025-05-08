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
    if (str.empty())
        return str;   
    
    bool is_negative = str[0] == '-';
    
    if (str.size() <= (is_negative ? 4 : 3))
        return str;
    
    size_t start_index = is_negative ? 1 : 0;
    size_t total_digits = str.size() - start_index;
    size_t first_comma_index = total_digits % 3;

    if (first_comma_index == 0)
        first_comma_index = 3;

    std::string formatted { str.substr(0, first_comma_index + start_index) + "," };
    int counter = 0;

    if (start_index == first_comma_index) 
    {
        first_comma_index++;
        total_digits++;
    }

    for (size_t i = first_comma_index; i < total_digits; i++)
    {   
        formatted += str[i];
        counter++;
        if (counter % 3 == 0 && i != total_digits - 1) 
            formatted += ',';
    }

    return formatted;
}
