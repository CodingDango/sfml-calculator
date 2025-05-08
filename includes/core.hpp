#ifndef CORE_HPP
#define CORE_HPP

#include "assets.hpp"
#include "calc.hpp"
#include "ui_elements.hpp"
#include <cmath>

#include <SFML/Graphics.hpp>

namespace core
{   
    namespace config 
    {
        // -- Configuration for prepareButtons function --
        inline static const sf::Vector2f GRID_STARTING_POINT { 20.0f, 200.0f };
        inline static const sf::Vector2f BLOCK_SIZE { 120.0f, 100.0f };
        inline static const int BLOCKS_PER_ROW  = 4;
        inline static const int MARGIN_X_PX     = 27;
        inline static const int MARGIN_Y_PX     = 20;

        // -- Configurations for prepareCopyableTexts --

        // All Texts
        inline static const sf::Color TEXT_HOVER_FILL_COLOR { 166, 169, 225 };
        inline static const auto TEXT_STYLE = sf::Text::Bold;
        inline static const size_t TEXT_CHAR_LIMIT = 16;

        // Input Text
        inline static const size_t INPUT_TEXT_FONT_SIZE = 50;
        inline static const sf::Vector2f INPUT_TEXT_POSITION { 20, 125 };

        // Result Text
        inline static const size_t RESULT_TEXT_FONT_SIZE = 40;
        inline static const sf::Vector2f RESULT_TEXT_POSITION { 20, 23.077 };
        inline static const sf::Color RESULT_TEXT_FILL_COLOR  {148, 148, 148};
        
        // Operation Text
        inline static const size_t OPERATION_TEXT_FONT_SIZE = 45;
        inline static const sf::Vector2f OPERATION_TEXT_POSITION { 535, 18 };
        inline static const sf::Color OPERATION_TEXT_FILL_COLOR  {148, 148, 148};
    }

    void prepareButtons(
        ui::ButtonContainer& container, 
        calc::CalculatorOperationContainer& calc_data
    );

    void addButtonFunction(
        ui::Button& btn, 
        const assets::ButtonInitializerData& initializer,
        calc::CalculatorOperationContainer& calc_data
    );

    void prepareCopyableTexts(
        ui::CopyableTextContainer& container, 
        calc::CalculatorOperationContainer& calc_data
    );
}

#endif