#include "input.hpp"

void input::keyOperations(calc::CalculatorOperationContainer& calc_data, const sf::Event& event)
{   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) 
        calc_data.backspace();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) || event.text.unicode == '=')
        calc_data.equal();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) || event.text.unicode == '+')
        calc_data.add();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) || event.text.unicode == '-')
        calc_data.subtract();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply) || event.text.unicode == '*')
        calc_data.multiply();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide) || event.text.unicode == '/')
        calc_data.divide();

    else if (isdigit(event.text.unicode) || event.text.unicode == '.') 
    {  
        // This is guaranteed to be a digit character. can be period.
        char character = event.text.unicode;
        calc_data.add_digit(character);
    }
}