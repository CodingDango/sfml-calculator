#include "headers/entities.hpp"

//===============================================================
// class Button Public Methods
//===============================================================

Button::Button(std::function<void()> c_callback)
:
    Sprite(),
    click_callback(c_callback)
{
    normal_color = getColor();
    hover_color = utils::modifyColorByFactor(getColor(), 0.8);
}

Button::Button()
:
    Sprite(),
    click_callback()
{
    normal_color = getColor();
    hover_color = utils::modifyColorByFactor(getColor(), 0.8);
}

void Button::handleHover(const sf::Vector2f& mouse_pos)
{
    if (getGlobalBounds().contains(mouse_pos))
        setColor(hover_color);
    else
        setColor(normal_color);
}

void Button::handleClick(const sf::Vector2f& mouse_pos, const sf::Event& event)
{   
    if (
        getGlobalBounds().contains(mouse_pos)
        && event.mouseButton.button == sf::Mouse::Button::Left
    )
    {
        click_callback();
    }

    else
        setColor(normal_color);
}

void Button::setClickCallback(std::function<void()> c_callback)
{
    click_callback = c_callback;
}


//===============================================================
// struct ButtonContainer Public Methods
//===============================================================

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