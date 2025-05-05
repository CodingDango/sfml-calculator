#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include "clipboard.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <cctype>
#include <functional>
#include <sstream>


//===============================================================
// Button related declarations
//===============================================================

namespace ui 
{
    class Button : public sf::Sprite
    {   
    public:
        Button(std::function<void()> callback);
        Button();

        void handleHover(const sf::Vector2f& mouse_pos);
        void handleClick(const sf::Vector2f& mouse_pos, const sf::Event& event);
        void setClickCallback(std::function<void()> callback);

    private:
        std::function<void()> m_click_callback;
        sf::Color m_hover_color;
        sf::Color m_normal_color;
    };

    class ButtonContainer
    {   
    public:
        void addButton(const Button& btn);
        void drawButtons(sf::RenderWindow& window);
        void checkForPress(const sf::Vector2f& mouse_pos, const sf::Event& event);
        void checkForHover(const sf::Vector2f& mouse_pos);
        
        std::vector<Button>::const_iterator begin() const;
        std::vector<Button>::const_iterator end() const;
        std::vector<Button>::const_reference back() const;

    private:
        std::vector<Button> m_buttons;
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
            size_t font_size,
            size_t char_limit,
            bool should_format
        )
        :   sf::Text        ( "", font, font_size ),
            m_value         { stringable_value },
            m_hover_color   {},
            m_normal_color  { sf::Color::White },
            m_char_limit    { char_limit },
            m_should_format { should_format }          
        {
            update();
        }

        void update()
        {  
            std::ostringstream oss {};
            oss << m_value;
            std::string result = oss.str();
            std::stringstream ss { result };
            
            // Format
            if (m_should_format && result.size() != 0)
            {   
                // Remove the . from the double.
                // This loss of data is intentional
                long long num {};
                ss >> num;
                std::string formatted_number = utils::format_number(std::to_string(num));
                const size_t dot_index = result.find('.');

                if (dot_index != std::string::npos)
                    // Formatted truncated integer + decimal part
                    result = formatted_number + result.substr(dot_index, result.size() - dot_index);
        
                else
                    result = formatted_number;
            }

            // Limit characters
            if (result.size() > m_char_limit)
                setString(result.substr(0, m_char_limit) + "...");
            else
                setString(result);
        }

        void checkForHover(const sf::Vector2f& mouse_pos)
        {
            if (getGlobalBounds().contains(mouse_pos)) 
                Text::setFillColor(m_hover_color);
            else
                Text::setFillColor(m_normal_color);
        }

        void setNormalFillColor(const sf::Color& color)
        {
            m_normal_color = color;
        }

        void setHoverColor(const sf::Color& color)
        {
            m_hover_color = color;
        }
        
        void setCharLimit(size_t limit)
        {
            m_char_limit = limit;
        }

    private:
        T& m_value;
        sf::Color m_normal_color;
        sf::Color m_hover_color;
        size_t m_char_limit;
        bool m_should_format;
    }; 

    struct CopyableTextContainer
    {
        std::vector<CopyableText<char>> m_char_texts; 
        std::vector<CopyableText<std::string>> m_string_texts;

        void updateAll();
        void drawTexts(sf::RenderWindow& target);
        bool checkForPress(const sf::Vector2f& mouse_pos, const sf::Event& event, HWND owner_hwnd);
        void checkForHover(const sf::Vector2f& mouse_pos);
    };
}

#endif