#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>

class Button : public sf::Sprite
{   
public:
    Button(std::function<void()> c_callback);
    void handleHover(const sf::Vector2f& mouse_pos);
    void handleClick(const sf::Vector2f& mouse_pos, const sf::Event& event);

private:
    std::function<void()> click_callback;
};

struct ButtonContainer : public std::vector<Button>
{   
    void drawButtons(sf::RenderWindow& window);
    void checkForClick(const sf::Vector2f& mouse_pos, const sf::Event& event);
    void checkForHover(const sf::Vector2f& mouse_pos);
};