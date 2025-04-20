#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "entities.hpp"

namespace calc 
{   
    // Values for buttons
    const static std::vector<std::string> button_values = {
        // First row
        "clear",
        "del",
        "=",

        // Second row
        "0",
        "1",
        "2",
        "+",

        // Third row
        "3",
        "4",
        "5",
        "-",

        // Fourth row
        "6",
        "7",
        "8",
        "*",
        
        // Fifth row
        "9",
        ".",
        "empty",
        "/"
    };



    class CalculatorOperationContainer
    {   
    public:
        std::string input {};
        double first_num {};
        char operation {};
        bool is_first_num_inputted = false;

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


namespace helpers 
{
    sf::Texture loadTextureFromFile(const std::string& path);

    void prepareButtons(
        ButtonContainer& container, 
        calc::CalculatorOperationContainer& calc_data
    );

    sf::Color modifyColorByFactor(sf::Color color, float factor);
}