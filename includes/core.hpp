#ifndef CORE_HPP
#define CORE_HPP

#include "assets.hpp"
#include "calc.hpp"
#include "entities.hpp"

#include <SFML/Graphics.hpp>

namespace core
{   
    void prepareButtons(
        entity::ButtonContainer& container, 
        calc::CalculatorOperationContainer& calc_data
    );

    void addButtonFunction(
        entity::Button& btn, 
        const assets::ButtonInitializerData& initializer,
        calc::CalculatorOperationContainer& calc_data
    );

    void prepareCopyableTexts(entity::CopyableTextContainer& container, calc::CalculatorOperationContainer& calc_data);
}

#endif