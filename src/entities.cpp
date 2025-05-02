#include "entities.hpp"

//===============================================================
// class Button Public Methods
//===============================================================

entity::Button::Button(std::function<void()> c_callback)
:
    Sprite(),
    click_callback(c_callback)
{
    normal_color = getColor();
    hover_color = utils::modifyColorByFactor(getColor(), 0.8);
}

entity::Button::Button()
:
    Sprite(),
    click_callback()
{
    normal_color = getColor();
    hover_color = utils::modifyColorByFactor(getColor(), 0.8);
}

void entity::Button::handleHover(const sf::Vector2f& mouse_pos)
{
    if (getGlobalBounds().contains(mouse_pos))
        setColor(hover_color);
    else
        setColor(normal_color);
}

void entity::Button::handleClick(const sf::Vector2f& mouse_pos, const sf::Event& event)
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

void entity::Button::setClickCallback(std::function<void()> c_callback)
{
    click_callback = c_callback;
}


//===============================================================
// struct ButtonContainer Public Methods
//===============================================================

void entity::ButtonContainer::drawButtons(sf::RenderWindow& window)
{
    for (auto& btn : *this)
    {
        window.draw(btn);
    }
}

void entity::ButtonContainer::checkForClick(const sf::Vector2f& mouse_pos, const sf::Event& event)
{
    for (auto& btn : *this)
    {
        btn.handleClick(mouse_pos, event);
    }
}

void entity::ButtonContainer::checkForHover(const sf::Vector2f& mouse_pos)
{
    for (auto& btn : *this)
    {
        btn.handleHover(mouse_pos);
    }
}


//===============================================================
// struct CopyableTextContainer definitions
//===============================================================

void entity::CopyableTextContainer::updateAll()
{
    for (auto& c : char_texts) { c.update(); }
    for (auto& s : string_texts) { s.update(); } 
}

void entity::CopyableTextContainer::drawAll(sf::RenderWindow& target)
{
    for (auto& c : char_texts) { target.draw(c); }
    for (auto& s : string_texts) { target.draw(s); }
}

bool entity::CopyableTextContainer::checkForPress(const sf::Vector2f& mouse_pos, const sf::Event& event, HWND owner_hwnd)
{
    bool has_text_been_clicked = false;

    for (auto& c : char_texts) 
    { 
        if (c.getGlobalBounds().contains(mouse_pos) && event.mouseButton.button == sf::Mouse::Left)
        {
            clipboard::copyStringToClipboard(c.getString(), owner_hwnd);
            has_text_been_clicked = true;
        }
    }

    for (auto& s : string_texts) 
    { 
        if (s.getGlobalBounds().contains(mouse_pos) && event.mouseButton.button == sf::Mouse::Left)
        {
            clipboard::copyStringToClipboard(s.getString(), owner_hwnd);
            has_text_been_clicked = true;
        }
    }
    
    return has_text_been_clicked;
}   

void entity::CopyableTextContainer::checkForHover(const sf::Vector2f& mouse_pos)
{
    for (auto& c : char_texts) { c.checkForHover(mouse_pos); }
    for (auto& s : string_texts) { s.checkForHover(mouse_pos); }
}   