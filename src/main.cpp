#include "assets.hpp"
#include "core.hpp"
#include "calc.hpp"
#include "clipboard.hpp"
#include "entities.hpp"
#include "input.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

const int WINDOW_WIDTH_PX = 600;
const int WINDOW_HEIGHT_PX = 800;
const sf::Color background_color {17, 17, 17};

int main()
{
    sf::RenderWindow window {
        sf::VideoMode({WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX}), 
        "Calculator"
    };

    // For clipboard
    HWND hwnd = static_cast<HWND>(window.getSystemHandle());

    // Core prep for buttons
    calc::CalculatorOperationContainer calc_data {};
    entity::ButtonContainer all_buttons {};
    core::prepareButtons(all_buttons, calc_data);
    
    // Prepare the text boxes
    entity::CopyableTextContainer texts {};
    core::prepareCopyableTexts(texts, calc_data);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f mouse_pos (sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) 
        {   
            switch (event.type)
            {
            case (sf::Event::Closed):
                window.close();
                break;

            case (sf::Event::MouseButtonPressed):
                all_buttons.checkForClick(mouse_pos, event);
                texts.checkForPress(mouse_pos, event, hwnd);
                break;

            case (sf::Event::TextEntered):
                input::handleTextEntered(calc_data, event);
                break;

            case (sf::Event::KeyPressed):
                input::handleKeyPress(calc_data, event);
                break;
            }
        }  
         
        // Update
        all_buttons.checkForHover(mouse_pos);
        texts.updateAll();

        // Draw
        window.clear(background_color);
        all_buttons.drawButtons(window);
        texts.drawAll(window);
        window.display();
    }
}