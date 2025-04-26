#include "input.hpp"

void input::keyOperations(calc::CalculatorOperationContainer& calc_data, const sf::Event& event)
{   
    if (event.type == sf::Event::T)

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) 
        calc_data.backspace();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        calc_data.equal();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        calc_data.add();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        calc_data.subtract();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply))
        calc_data.multiply();

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide))
        calc_data.divide();

    else 
    {   
        sf::Event::TextEvent::unicode
        // This is guaranteed to be a digit character. can be period.
        char character = sf::Keyboard::isKeyPressed(sf::)
        btn.setClickCallback([&calc_data, digit](){ calc_data.add_digit(digit); });
    }
}