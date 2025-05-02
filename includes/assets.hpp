#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace assets 
{       
    struct ButtonInitializerData
    {   
        const std::string value;
        const sf::Texture texture;

        ButtonInitializerData(
            const std::string& val,
            const sf::Texture& text
        )
        :   value(val), texture(text) 
        {}
    }; 

    extern const std::vector<ButtonInitializerData> button_initializers;
    extern const sf::Font my_font;
    extern const sf::Texture texture_copy_notification;
}

#endif