#ifndef CORE_HPP
#define CORE_HPP

#include "assets.hpp"
#include "calc.hpp"
#include "ui_elements.hpp"

#include <SFML/Graphics.hpp>

namespace core
{   
    void prepareButtons(
        ui::ButtonContainer& container, 
        calc::CalculatorOperationContainer& calc_data
    );

    void addButtonFunction(
        ui::Button& btn, 
        const assets::ButtonInitializerData& initializer,
        calc::CalculatorOperationContainer& calc_data
    );

    void prepareCopyableTexts(ui::CopyableTextContainer& container, calc::CalculatorOperationContainer& calc_data);
}

#endif