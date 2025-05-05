#include "input.hpp"

void input::handleKeyPress(
    calc::CalculatorOperationContainer& calc_data, 
    const sf::Event& event
)
{
    if (event.key.control)
    {
        switch (event.key.code)
        {
        case (sf::Keyboard::C):
            calc_data.clear();
            break;
        }
    }
    else
    {
        switch (event.key.code)
        {
        case (sf::Keyboard::Add):
            calc_data.add();
            break;
    
        case (sf::Keyboard::Subtract):
            calc_data.subtract();
            break;
    
        case (sf::Keyboard::Slash):
            calc_data.divide();
            break;
    
        case (sf::Keyboard::Enter):
            calc_data.equal();
            break;
    
        case (sf::Keyboard::BackSpace):
            calc_data.backspace();
            break;
        }
    } 
}

void input::handleTextEntered(
    calc::CalculatorOperationContainer& calc_data, 
    const sf::Event& event
)
{
    if (isdigit(event.text.unicode) || event.text.unicode == '.')
    {
        calc_data.add_digit(event.text.unicode);
        return;
    }

    // If the pressed button outputted an operator.
    switch (event.text.unicode)
    {
    case ('+'):
        calc_data.add();
        break;
    case ('-'):
        calc_data.subtract();
        break;
    case ('*'):
        calc_data.multiply();
        break;
    case ('/'):
        calc_data.divide();
        break;
    case ('='):
        calc_data.equal();
        break;
    }
}