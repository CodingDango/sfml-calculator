#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "clipboard.hpp"

#include <SFML/Graphics.hpp>

#include <functional>
#include <sstream>

// Forward declarations from helpers.hpp
namespace utils
{
    sf::Color modifyColorByFactor(sf::Color color, float factor); 
}

//===============================================================
// Button related declarations
//===============================================================

namespace entity 
{
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


    //===============================================================
    // CopyableText related content
    //===============================================================

    template <typename T>
    class CopyableText : public sf::Text 
    {   
    public:
        CopyableText(
            T& stringable_value, 
            const sf::Font& font, 
            int font_size
        )
        :   sf::Text        ("", font, font_size),
            value           {stringable_value},
            hover_color     {},
            normal_color    { sf::Color::White } 
        {
            update();
        }

        void update()
        {   
            std::ostringstream oss {};
            oss << value;
            setString(oss.str());
        }

        void checkForHover(const sf::Vector2f& mouse_pos)
        {
            if (getGlobalBounds().contains(mouse_pos)) 
                Text::setFillColor(hover_color);
            else
                Text::setFillColor(normal_color);
        }

        void setNormalFillColor(const sf::Color& color)
        {
            normal_color = color;
        }

        void setHoverColor(const sf::Color& color)
        {
            hover_color = color;
        }
        
    private:
        T& value;
        sf::Color normal_color;
        sf::Color hover_color;
    }; 

    struct CopyableTextContainer
    {
        std::vector<CopyableText<char>> char_texts; 
        std::vector<CopyableText<std::string>> string_texts;

        void updateAll();
        void drawAll(sf::RenderWindow& target);
        void checkForPress(const sf::Vector2f& mouse_pos, const sf::Event& event, HWND owner_hwnd);
        void checkForHover(const sf::Vector2f& mouse_pos);
    };
}

#endif