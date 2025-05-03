#include "assets.hpp"
#include "core.hpp"
#include "calc.hpp"
#include "clipboard.hpp"
#include "entities.hpp"
#include "input.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{   
    const int window_width_px = 600;
    const int window_height_px = 800;
    const sf::Color bg_color {17, 17, 17};

    sf::RenderWindow window {sf::VideoMode({window_width_px, window_height_px}), "Calculator"};
    window.setFramerateLimit(60);

    sf::Clock clock;

    // For clipboard
    HWND hwnd = static_cast<HWND>(window.getSystemHandle());
    
    // Core prep for buttons
    calc::CalculatorOperationContainer calc_data {};
    entity::ButtonContainer all_buttons          {};
    
    core::prepareButtons(all_buttons, calc_data);
    
    // Prepare the text boxes
    entity::CopyableTextContainer texts {};
    core::prepareCopyableTexts(texts, calc_data);

    // Copy notification sprite
    sf::Sprite copy_notification {assets::texture_copy_notification};
    copy_notification.setColor(utils::modifyColorOpacity(copy_notification.getColor(), 0));
    copy_notification.setPosition(350, 26);
    
    while (window.isOpen())
    {
        float delta_time =      clock.restart().asSeconds();
        sf::Vector2f mouse_pos (sf::Mouse::getPosition(window));
        sf::Event event;

        while (window.pollEvent(event)) 
        {   
            switch (event.type)
            {
            case (sf::Event::Closed):
                window.close();
                break;

            case (sf::Event::MouseButtonPressed):

                all_buttons.checkForClick(mouse_pos, event);
                
                // evals to true if user clicked on a copyable text, which copies to the clipboard
                if (texts.checkForPress(mouse_pos, event, hwnd))
                    copy_notification.setColor(utils::modifyColorOpacity(copy_notification.getColor(), 255));
                    
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
        texts.checkForHover(mouse_pos);
        texts.updateAll();

        // Update copy notification (lowers the opacity overtime)
        double new_opacity = copy_notification.getColor().a - (100 * delta_time);
        copy_notification.setColor(utils::modifyColorOpacity(copy_notification.getColor(), new_opacity));
        
        // Draw
        window.clear(bg_color);
        all_buttons.drawButtons(window);
        texts.drawAll(window);
        window.draw(copy_notification);
        window.display();
    }
}