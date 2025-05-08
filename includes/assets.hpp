#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "utils.hpp"

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

    static inline const std::vector<ButtonInitializerData> button_initializers = {
        // First row
        ButtonInitializerData("clear", utils::loadTexture("./assets/op-btns/oper-clear.png")),
        ButtonInitializerData("del", utils::loadTexture("./assets/op-btns/oper-del.png")),
        ButtonInitializerData("/", utils::loadTexture("./assets/op-btns/oper-divide.png")),
            
        // Second row
        ButtonInitializerData("7", utils::loadTexture("./assets/num-btns/num-7.png")),
        ButtonInitializerData("8", utils::loadTexture("./assets/num-btns/num-8.png")),
        ButtonInitializerData("9", utils::loadTexture("./assets/num-btns/num-9.png")), 
        ButtonInitializerData("*", utils::loadTexture("./assets/op-btns/oper-multiply.png")),

        // Third row
        ButtonInitializerData("4", utils::loadTexture("./assets/num-btns/num-4.png")),
        ButtonInitializerData("5", utils::loadTexture("./assets/num-btns/num-5.png")),
        ButtonInitializerData("6", utils::loadTexture("./assets/num-btns/num-6.png")),
        ButtonInitializerData("-", utils::loadTexture("./assets/op-btns/oper-subtract.png")),

        // Fourth row
        ButtonInitializerData("1", utils::loadTexture("./assets/num-btns/num-1.png")),
        ButtonInitializerData("2", utils::loadTexture("./assets/num-btns/num-2.png")),
        ButtonInitializerData("3", utils::loadTexture("./assets/num-btns/num-3.png")),
        ButtonInitializerData("+", utils::loadTexture("./assets/op-btns/oper-add.png")),

        // Fifth row
        ButtonInitializerData("empty", utils::loadTexture("./assets/num-btns/num-empty.png")),
        ButtonInitializerData("0", utils::loadTexture("./assets/num-btns/num-0.png")),
        ButtonInitializerData(".", utils::loadTexture("./assets/num-btns/char-dot.png")),
        ButtonInitializerData("=", utils::loadTexture("./assets/op-btns/oper-equals.png")),
    }; 

    static inline const sf::Font my_font { utils::loadFont("./assets/fonts/YuGothM.ttc") };
    static inline const sf::Texture texture_copy_notification { utils::loadTexture("./assets/notify.png") };
}

#endif