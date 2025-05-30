#ifndef INPUT_HPP
#define INPUT_HPP

#include "calc.hpp"
#include <SFML/Window.hpp>

namespace input
{
    void handleKeyPress(calc::CalculatorOperationContainer& calc_data, const sf::Event& event);
    void handleTextEntered(calc::CalculatorOperationContainer& calc_data, const sf::Event& event);
} 

#endif