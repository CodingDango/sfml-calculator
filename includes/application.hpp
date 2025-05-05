#include "assets.hpp"
#include "core.hpp"
#include "calc.hpp"
#include "clipboard.hpp"
#include "ui_elements.hpp"
#include "input.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>

class Application
{
public:
    Application();
    void runApp();

private:
    // Config
    inline static const int WINDOW_WIDTH_PX    { 600 };    
    inline static const int WINDOW_HEIGHT_PX   { 800 };   

    inline static const sf::Color BG_COLOR                     { 17, 17, 17 };     
    inline static const double NOTIFICATION_FADE_SPEED_FACTOR  { 100 };    
    inline static const sf::Vector2f NOTIFICATION_POSITION     { 530, 100 };
    
    // System
    sf::RenderWindow m_window; 
    sf::Clock m_clock;
    HWND m_hwnd;                // For Windows specific clipboard operations

    // Application State And Data
    calc::CalculatorOperationContainer m_calc_operation; 
    ui::ButtonContainer m_button_container;          
    ui::CopyableTextContainer m_copyable_text_container; 
    
    // Unique UI Sprites
    sf::Sprite m_copy_notification;

    // Methods
    void prepareUISprites();
    void processEvents();
    void updateUISprites();
    void drawUISprites();
};