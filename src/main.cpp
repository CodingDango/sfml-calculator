#include "headers/entities.hpp"   
#include "headers/helpers.hpp"

const int WINDOW_WIDTH_PX = 655;
const int WINDOW_HEIGHT_PX = 1062;
const sf::Color background_color {17, 17, 17};

int main()
{
    sf::RenderWindow window {
        sf::VideoMode({WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX}), 
        "Calculator"
    };

    calc::CalculatorOperationContainer calc_data;
    ButtonContainer all_buttons {};
    
    helpers::prepareButtons(all_buttons, calc_data);

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
                std::cout << calc_data.input << '\n';
                std::cout << "First number: " << calc_data.first_num << '\n';
                std::cout << "Operator: " << calc_data.operation << '\n';
            }
        }  
         
        // Update
        all_buttons.checkForHover(mouse_pos);

        // Draw
        window.clear(background_color);
        all_buttons.drawButtons(window);
        window.display();
    }
}