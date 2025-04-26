#include "calc.hpp"

#include <SFML/Window.hpp>

namespace input
{
    enum class OperatorMapping 
    {
        Add,
        Del,
        Subtract,
        Multiply,
        Divide,
        Equals
    };

    void keyOperations(calc::CalculatorOperationContainer& calc_data, const sf::Event& event);
} 