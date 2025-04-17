#include "headers/entities.hpp"


Button::Button(std::function<void()> c_callback)
:
    Sprite(),
    click_callback(c_callback)
{}

void Button::handleHover(const sf::Vector2f& mouse_pos)
{
    if (getGlobalBounds().contains(mouse_pos))
        std::cout << "I am being hovered.\n";
}

void Button::handleClick(const sf::Vector2f& mouse_pos, const sf::Event& event)
{   
    if (
        getGlobalBounds().contains(mouse_pos)
        && event.mouseButton.button == sf::Mouse::Button::Left
    )
        click_callback();
}

void ButtonContainer::drawButtons(sf::RenderWindow& window)
{
    for (auto& btn : *this)
    {
        window.draw(btn);
    }
}

void ButtonContainer::checkForClick(const sf::Vector2f& mouse_pos, const sf::Event& event)
{
    for (auto& btn : *this)
    {
        btn.handleClick(mouse_pos, event);
    }
}

void ButtonContainer::checkForHover(const sf::Vector2f& mouse_pos)
{
    for (auto& btn : *this)
    {
        btn.handleHover(mouse_pos);
    }
}