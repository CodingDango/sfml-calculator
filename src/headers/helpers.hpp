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

    // Paths to the assets of these buttons
    static const std::vector<sf::Texture> button_texture_paths = {
        // First row of button, btnclear counts as buttons in width
        helpers::loadTextureFromFile("../assets/op-btns/btnclear.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btndel.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btnequal.png"),
    
        // Second row of the buttons
        helpers::loadTextureFromFile("../assets/num-btns/btn0.png"),
        helpers::loadTextureFromFile("../assets/num-btns/btn1.png"),
        helpers::loadTextureFromFile("../assets/num-btns/btn2.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btnplus.png"),
    
        // Third row of the buttons
        helpers::loadTextureFromFile("../assets/num-btns/btn3.png"),
        helpers::loadTextureFromFile("../assets/num-btns/btn4.png"),
        helpers::loadTextureFromFile("../assets/num-btns/btn5.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btndash.png"),
    
        // Fourth row of the buttons
        helpers::loadTextureFromFile("../assets/num-btns/btn6.png"),
        helpers::loadTextureFromFile("../assets/num-btns/btn7.png"),
        helpers::loadTextureFromFile("../assets/num-btns/btn8.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btnaster.png"),
    
        // Fifth row of the buttons
        helpers::loadTextureFromFile("../assets/num-btns/btn9.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btndot.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btnempty.png"),
        helpers::loadTextureFromFile("../assets/op-btns/btnslash.png"),
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

namespace core
{       
    void prepareButtons(
        ButtonContainer& container, 
        calc::CalculatorOperationContainer& calc_data
    );

    void addButtonFunction(
        Button& btn, 
        int value_index,
        calc::CalculatorOperationContainer& calc_data
    );
}