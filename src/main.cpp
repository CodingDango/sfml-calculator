#include "core.hpp"
#include "entities.hpp"
#include "input.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH_PX = 600;
const int WINDOW_HEIGHT_PX = 800;
const sf::Color background_color {17, 17, 17};

int main()
{
    sf::RenderWindow window {
        sf::VideoMode({WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX}), 
        "Calculator"
    };

    // Core prep for buttons
    calc::CalculatorOperationContainer calc_data {};
    entity::ButtonContainer all_buttons {};
    core::prepareButtons(all_buttons, calc_data);
    
    // Creating the first number textbox
    entity::DynamicText input_num_text {calc_data.input, assets::my_font, 50};
    input_num_text.setStyle(sf::Text::Bold);
    input_num_text.setPosition(30, 125);

    entity::DynamicText result_text {calc_data.result, assets::my_font, 40};
    result_text.setStyle(sf::Text::Bold);
    result_text.setFillColor(sf::Color(148, 148, 148, 100));
    result_text.setPosition(30, 26);
        
    entity::DynamicText operation_text {calc_data.operation, assets::my_font, 45};
    operation_text.setStyle(sf::Text::Bold);
    operation_text.setFillColor(sf::Color(148, 148, 148, 100));
    operation_text.setPosition(535, 26);
    
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f mouse_pos (sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                all_buttons.checkForClick(mouse_pos, event);
            }

            if (event.type == sf::Event::KeyPressed) 
            {
                // Detect keypresses
                input::keyOperations(calc_data, event);
            }
        }  
         
        // Update
        all_buttons.checkForHover(mouse_pos);
        input_num_text.update();
        result_text.update();
        operation_text.update();

        // Draw
        window.clear(background_color);
        all_buttons.drawButtons(window);
        window.draw(input_num_text);
        window.draw(result_text);
        window.draw(operation_text);
        window.display();
    }
}