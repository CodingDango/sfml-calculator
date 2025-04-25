#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>

// Forward declarations from helpers.hpp
namespace utils
{
    sf::Color modifyColorByFactor(sf::Color color, float factor);
}

// Declarations
class Button : public sf::Sprite
{   
public:
    Button(std::function<void()> c_callback);
    Button();

    void handleHover(const sf::Vector2f& mouse_pos);
    void handleClick(const sf::Vector2f& mouse_pos, const sf::Event& event);
    void setClickCallback(std::function<void()> c_callback);

private:
    std::function<void()> click_callback;
    sf::Color hover_color;
    sf::Color normal_color;
};

struct ButtonContainer : public std::vector<Button>
{   
    void drawButtons(sf::RenderWindow& window);
    void checkForClick(const sf::Vector2f& mouse_pos, const sf::Event& event);
    void checkForHover(const sf::Vector2f& mouse_pos);
};