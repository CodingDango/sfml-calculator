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

    using namespace helpers;    // Shorten the code

    static const std::vector<ButtonInitializerData> button_initializers = {

            // First row
            ButtonInitializerData("clear", loadTextureFromFile("../assets/op-btns/oper-clear.png")),
            ButtonInitializerData("del", loadTextureFromFile("../assets/op-btns/oper-del.png")),
            ButtonInitializerData("/", loadTextureFromFile("../assets/op-btns/oper-divide.png")),
            
            // Second row
            ButtonInitializerData("7", loadTextureFromFile("../assets/num-btns/num-7.png")),
            ButtonInitializerData("8", loadTextureFromFile("../assets/num-btns/num-8.png")),
            ButtonInitializerData("9", loadTextureFromFile("../assets/num-btns/num-9.png")),
            ButtonInitializerData("*", loadTextureFromFile("../assets/op-btns/oper-multiply.png")),
    
            // Third row
            ButtonInitializerData("4", loadTextureFromFile("../assets/num-btns/num-4.png")),
            ButtonInitializerData("5", loadTextureFromFile("../assets/num-btns/num-5.png")),
            ButtonInitializerData("6", loadTextureFromFile("../assets/num-btns/num-6.png")),
            ButtonInitializerData("-", loadTextureFromFile("../assets/op-btns/oper-subtract.png")),
    
            // Fourth row
            ButtonInitializerData("1", loadTextureFromFile("../assets/num-btns/num-1.png")),
            ButtonInitializerData("2", loadTextureFromFile("../assets/num-btns/num-2.png")),
            ButtonInitializerData("3", loadTextureFromFile("../assets/num-btns/num-3.png")),
            ButtonInitializerData("+", loadTextureFromFile("../assets/op-btns/oper-add.png")),

            // Fifth row
            ButtonInitializerData("empty", loadTextureFromFile("../assets/num-btns/num-empty.png")),
            ButtonInitializerData("0", loadTextureFromFile("../assets/num-btns/num-0.png")),
            ButtonInitializerData(".", loadTextureFromFile("../assets/num-btns/char-dot.png")),
            ButtonInitializerData("=", loadTextureFromFile("../assets/op-btns/oper-equals.png")),
    }; 
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