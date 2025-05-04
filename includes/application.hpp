#include "assets.hpp"
#include "core.hpp"
#include "calc.hpp"
#include "clipboard.hpp"
#include "entities.hpp"
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
    static constexpr int WINDOW_WIDTH_PX     { 600 };    
    static constexpr int WINDOW_HEIGHT_PX    { 800 };   

    static inline sf::Color BG_COLOR                          { 17, 17, 17 };     
    static constexpr double NOTIFICATION_FADE_SPEED_FACTOR    { 100 };    
    static inline sf::Vector2f NOTIFICATION_POSITION          { 537.291, 73.584 };
    
    // System
    sf::RenderWindow m_window; 
    sf::Clock m_clock;
    HWND m_hwnd;

    // Application State And Data
    calc::CalculatorOperationContainer m_calc_operation; 
    entity::ButtonContainer m_button_container;          
    entity::CopyableTextContainer m_copyable_text_container; 
    
    // UI Sprites
    sf::Sprite m_copy_notification;

    // Methods
    void prepareUISprites();
    void processEvents();
    void updateSprites();
    void drawSprites();
};