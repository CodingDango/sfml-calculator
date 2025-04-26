#include "helpers.hpp"

const int WINDOW_WIDTH_PX = 600;
const int WINDOW_HEIGHT_PX = 800;
const sf::Color background_color {17, 17, 17};

int main()
{
    sf::RenderWindow window {
        sf::VideoMode({WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX}), 
        "Calculator"
    };

    calc::CalculatorOperationContainer calc_data {};
    ButtonContainer all_buttons {};

    core::prepareButtons(all_buttons, calc_data);
    

    // Creating the first number textbox
    DynamicText input_num_text {calc_data.input, assets::my_font, 50};
    input_num_text.setStyle(sf::Text::Bold);
    input_num_text.setPosition(30, 125);

    DynamicText result_text {calc_data.result, assets::my_font, 40};
    result_text.setStyle(sf::Text::Bold);
    result_text.setFillColor(sf::Color(148, 148, 148, 100));
    result_text.setPosition(30, 26);
        
    DynamicText operation_text {calc_data.operation, assets::my_font, 45};
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
                input_num_text.update();
                result_text.update();
                operation_text.update();
            }
        }  
         
        // Update
        all_buttons.checkForHover(mouse_pos);

        // Draw
        window.clear(background_color);
        all_buttons.drawButtons(window);
        window.draw(input_num_text);
        window.draw(result_text);
        window.draw(operation_text);
        window.display();
    }
}