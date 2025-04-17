#include <helpers.hpp>

sf::Texture helpers::loadTextureFromFile(const std::string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

void helpers::prepareButtons(ButtonContainer& container)
{
    static const std::vector<sf::Texture> button_textures = {
        // First row of button, btnclear counts as buttons in width
        loadTextureFromFile("../assets/op-btns/btnclear.png"),
        loadTextureFromFile("../assets/op-btns/btndel.png"),
        loadTextureFromFile("../assets/op-btns/btnequal.png"),
    
        // Second row of the buttons
        loadTextureFromFile("../assets/num-btns/btn0.png"),
        loadTextureFromFile("../assets/num-btns/btn1.png"),
        loadTextureFromFile("../assets/num-btns/btn2.png"),
        loadTextureFromFile("../assets/op-btns/btnplus.png"),
    
        // Third row of the buttons
        loadTextureFromFile("../assets/num-btns/btn3.png"),
        loadTextureFromFile("../assets/num-btns/btn4.png"),
        loadTextureFromFile("../assets/num-btns/btn5.png"),
        loadTextureFromFile("../assets/op-btns/btndash.png"),
    
        // Fourth row of the buttons
        loadTextureFromFile("../assets/num-btns/btn6.png"),
        loadTextureFromFile("../assets/num-btns/btn7.png"),
        loadTextureFromFile("../assets/num-btns/btn8.png"),
        loadTextureFromFile("../assets/op-btns/btnaster.png"),
    
        // Fifth row of the buttons
        loadTextureFromFile("../assets/num-btns/btn9.png"),
        loadTextureFromFile("../assets/op-btns/btndot.png"),
        loadTextureFromFile("../assets/op-btns/btnempty.png"),
        loadTextureFromFile("../assets/op-btns/btnslash.png"),
    }; 

    const sf::Vector2f STARTING_POINT = {17.0f, 266.0f};
    const int MARGIN_PX = 20;
    const int BUTTONS_PER_ROW = 4;

    int X {STARTING_POINT.x};
    int Y {STARTING_POINT.y};
    int BUTTON_COUNTER {};

    for (int i = 0; i < button_textures.size(); i++)
    {       
        // Clear button.. it takes 2 boxes
        if (i == 0)
        {
            BUTTON_COUNTER += 2;
            Button clear_button { [](){ std::cout << "I am a clear button!\n";} };
            clear_button.setTexture(button_textures[0]);
            clear_button.setPosition(STARTING_POINT);
            container.push_back(clear_button);
            continue;
        } else 
        {
            BUTTON_COUNTER++;
        }

        // Updating X and Y values
        if ((BUTTON_COUNTER - 1)% BUTTONS_PER_ROW == 0)
        {   
            // Get height of last element and add the gap or magin
            Y += (container.back().getTexture()->getSize().y) + MARGIN_PX;    
            X = STARTING_POINT.x;
        } else 
        {
            X += (container.back().getTexture()->getSize().x) + MARGIN_PX;
        }

        Button button { [](){ std::cout << "I am a button!\n";} };
        button.setTexture(button_textures[i]);
        button.setPosition({X, Y});
        container.push_back(button);
    }
}