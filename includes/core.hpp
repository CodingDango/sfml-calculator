#pragma once

#include "assets.hpp"
#include "calc.hpp"
#include "entities.hpp"
#include <SFML/Graphics.hpp>

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