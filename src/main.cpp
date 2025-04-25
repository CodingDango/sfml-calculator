#include "headers/entities.hpp"   
#include "headers/helpers.hpp"

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

    // Load in font for the text
    sf::Font font {};
    if (!font.loadFromFile("../assets/fonts/YuGothM.ttc"))
    {
        std::cerr << "Font coulnd't be loaded\n";
        return -1;
    }

    // Creating the first number textbox
    sf::Text input_num_text {"0", font, 50};
    input_num_text.setStyle(sf::Text::Bold);
    input_num_text.setPosition(30, 125);

    sf::Text result_text {"0", font, 40};
    result_text.setStyle(sf::Text::Bold);
    result_text.setFillColor(sf::Color(148, 148, 148, 100));
    result_text.setPosition(30, 26);
        
    sf::Text operation_text {"~", font, 45};
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

                input_num_text.setString(calc_data.input);
                result_text.setString(std::to_string(calc_data.result));
                operation_text.setString(calc_data.operation);
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