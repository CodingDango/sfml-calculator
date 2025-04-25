#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "entities.hpp"

namespace utils
{
    sf::Texture loadTexture(const std::string& path);

    sf::Color modifyColorByFactor(sf::Color color, float factor);

    sf::Font loadFont(const std::string& path);
}

namespace calc 
{   
    class CalculatorOperationContainer
    {   
    public:
        std::string input {};
        double result {};
        char operation {};
        bool is_operation_inputted = false;

        void add_digit(char digit);
        void reset();
        void backspace();
        void clear();
        void add();
        void subtract();
        void equal();
        void multiply();
        void divide();

    private:
        double evaluate(double a, double b, char operation) const;
        void doOperatorOperation(char operation);
        void applyResult(std::stringstream& ss);
    }; 
}

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
}

namespace core
{       
    void prepareButtons(
        ButtonContainer& container, 
        calc::CalculatorOperationContainer& calc_data
    );

    void addButtonFunction(
        Button& btn, 
        const assets::ButtonInitializerData& initializer,
        calc::CalculatorOperationContainer& calc_data
    );
}