#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "entities.hpp"

namespace helpers
{
    sf::Texture loadTextureFromFile(const std::string& path);

    sf::Color modifyColorByFactor(sf::Color color, float factor);
}

namespace calc 
{   
    class CalculatorOperationContainer
    {   
    public:
        std::string input {};
        double first_num {};
        char operation {};
        bool is_first_num_inputted = false;
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
    const auto& load = helpers::loadTextureFromFile; // Shorten the code for loading.

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