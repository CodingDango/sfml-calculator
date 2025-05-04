#include "application.hpp"

Application::Application()
:   m_window { sf::VideoMode(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX), "Calculator" },
    m_hwnd { static_cast<HWND>(m_window.getSystemHandle()) }
{
    m_window.setFramerateLimit(60);
}

void Application::runApp()
{
    prepareUISprites();

    while (m_window.isOpen())
    {
        processEvents();
        updateSprites();
        drawSprites();
    }
}

void Application::prepareUISprites()
{
    core::prepareButtons(m_button_container, m_calc_operation);
    core::prepareCopyableTexts(m_copyable_text_container, m_calc_operation);

    // Set starting opacity to 0
    m_copy_notification.setTexture(assets::texture_copy_notification);
    m_copy_notification.setColor(utils::modifyColorOpacity(m_copy_notification.getColor(), 0));
    m_copy_notification.setPosition(NOTIFICATION_POSITION);
}

void Application::processEvents()
{
    sf::Vector2f mouse_pos ( sf::Mouse::getPosition(m_window) );
    sf::Event event;
    static int counter {};

    while (m_window.pollEvent(event)) 
    {   
        switch (event.type)
        {
        case (sf::Event::Closed):
            m_window.close();
            break;

        case (sf::Event::MouseButtonPressed):

            // Sets the opacity of copy notification sprite to full
            if (m_copyable_text_container.checkForPress(mouse_pos, event, m_hwnd))
                m_copy_notification.setColor(utils::modifyColorOpacity(m_copy_notification.getColor(), 255));
            
            m_button_container.checkForPress(mouse_pos, event);
  
            break;

        case (sf::Event::TextEntered):
            input::handleTextEntered(m_calc_operation, event);
            std::cout << ++counter << '\n';
            break;

        case (sf::Event::KeyPressed):
            input::handleKeyPress(m_calc_operation, event);
            break;
        }
    }  
}

void Application::updateSprites()
{   
    sf::Vector2f mouse_pos ( sf::Mouse::getPosition(m_window) );
    float dt { m_clock.restart().asSeconds() };

    m_button_container.checkForHover(mouse_pos);
    m_copyable_text_container.checkForHover(mouse_pos);
    m_copyable_text_container.updateAll();

    // Update copy notification (lowers the opacity overtime)
    double new_opacity = m_copy_notification.getColor().a - (NOTIFICATION_FADE_SPEED_FACTOR * dt);
    m_copy_notification.setColor(utils::modifyColorOpacity(m_copy_notification.getColor(), new_opacity));
}

void Application::drawSprites()
{
    m_window.clear(BG_COLOR);
    m_button_container.drawButtons(m_window);
    m_copyable_text_container.drawTexts(m_window);
    m_window.draw(m_copy_notification);
    m_window.display();
}