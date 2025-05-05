#include "ui_elements.hpp"

//===============================================================
// class Button Public Methods
//===============================================================

ui::Button::Button(std::function<void()> callback)
:
    Sprite              {},
    m_click_callback    { callback },
    m_normal_color      { getColor() },
    m_hover_color       { utils::modifyColorByFactor(getColor(), 0.8) }
{}

ui::Button::Button()
:
    Sprite              {}, 
    m_click_callback    {},
    m_normal_color      { getColor() },
    m_hover_color       { utils::modifyColorByFactor(getColor(), 0.8) }
{}

void ui::Button::handleHover(const sf::Vector2f& mouse_pos)
{
    if (getGlobalBounds().contains(mouse_pos))
        setColor(m_hover_color);
    else
        setColor(m_normal_color);
}

void ui::Button::handleClick(const sf::Vector2f& mouse_pos, const sf::Event& event)
{   
    if (getGlobalBounds().contains(mouse_pos)
        && event.mouseButton.button == sf::Mouse::Button::Left)
    {
        m_click_callback();
    }
}

void ui::Button::setClickCallback(std::function<void()> callback)
{
    m_click_callback = callback;
}


//===============================================================
// struct ButtonContainer Public Methods
//===============================================================

void ui::ButtonContainer::addButton(const Button& btn)
{
    m_buttons.push_back(btn);
}

void ui::ButtonContainer::drawButtons(sf::RenderWindow& window)
{
    for (auto& btn : m_buttons)
    {
        window.draw(btn);
    }
}

void ui::ButtonContainer::checkForPress(const sf::Vector2f& mouse_pos, const sf::Event& event)
{
    for (auto& btn : m_buttons)
    {
        btn.handleClick(mouse_pos, event);
    }
}

void ui::ButtonContainer::checkForHover(const sf::Vector2f& mouse_pos)
{
    for (auto& btn : m_buttons)
    {
        btn.handleHover(mouse_pos);
    }
}

std::vector<ui::Button>::const_iterator ui::ButtonContainer::begin() const 
{
    return m_buttons.begin();
}

std::vector<ui::Button>::const_iterator ui::ButtonContainer::end() const
{
    return m_buttons.end();
}

std::vector<ui::Button>::const_reference ui::ButtonContainer::back() const
{
    return m_buttons.back();
}


//===============================================================
// struct CopyableTextContainer definitions
//===============================================================

void ui::CopyableTextContainer::updateAll()
{
    for (auto& c : m_char_texts) { c.update(); }
    for (auto& s : m_string_texts) { s.update(); } 
}

void ui::CopyableTextContainer::drawTexts(sf::RenderWindow& target)
{
    for (auto& c : m_char_texts) { target.draw(c); }
    for (auto& s : m_string_texts) { target.draw(s); }
}

bool ui::CopyableTextContainer::checkForPress(const sf::Vector2f& mouse_pos, const sf::Event& event, HWND owner_hwnd)
{
    bool has_text_been_clicked = false;

    for (auto& c : m_char_texts) 
    { 
        if (c.getGlobalBounds().contains(mouse_pos) && event.mouseButton.button == sf::Mouse::Left)
        {
            clipboard::copyStringToClipboard(c.getString(), owner_hwnd);
            has_text_been_clicked = true;
        }
    }

    for (auto& s : m_string_texts) 
    { 
        if (s.getGlobalBounds().contains(mouse_pos) && event.mouseButton.button == sf::Mouse::Left)
        {
            clipboard::copyStringToClipboard(s.getString(), owner_hwnd);
            has_text_been_clicked = true;
        } 
    }
    
    return has_text_been_clicked;
}   

void ui::CopyableTextContainer::checkForHover(const sf::Vector2f& mouse_pos)
{
    for (auto& c : m_char_texts) { c.checkForHover(mouse_pos); }
    for (auto& s : m_string_texts) { s.checkForHover(mouse_pos); }
}   