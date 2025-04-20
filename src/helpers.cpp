#include "headers/helpers.hpp"

//===============================================================
// Class CalculatorOperationContainer Public Methods Definitions
//===============================================================

void calc::CalculatorOperationContainer::add_digit(char digit)
{   
    // Checks if period is already input, to avoid multiple periods.
    if (digit == '.' && input.find_first_of(digit) == std::string::npos)
        return;
    input += digit;
}

void calc::CalculatorOperationContainer::reset()
{   
    input.clear();
    first_num = double();
    operation = char();
    is_first_num_inputted = false;
}

void calc::CalculatorOperationContainer::backspace()
{
    input.pop_back();
}

void calc::CalculatorOperationContainer::clear()
{
    input.clear();
}

void calc::CalculatorOperationContainer::equal()
{
    if (!is_first_num_inputted 
        && input.size() == 0)
        return;
    
    std::stringstream ss {input};   // ss contains the second number
    applyResult(ss);                       
    input.clear();
}

void calc::CalculatorOperationContainer::add()
{
    doOperatorOperation('+');
}

void calc::CalculatorOperationContainer::subtract()
{
    doOperatorOperation('-');
}

void calc::CalculatorOperationContainer::multiply()
{
    doOperatorOperation('*');
}

void calc::CalculatorOperationContainer::divide()
{
    doOperatorOperation('/');
}

//===============================================================
// Class CalculatorOperationContainer Private Methods Definitions
//===============================================================

double calc::CalculatorOperationContainer::evaluate(
    double a,
    double b, 
    char operation
) const
{
    switch (operation)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;

    default:
        return -69;
    }
}

void calc::CalculatorOperationContainer::doOperatorOperation(char operation)
{   
    if (!is_first_num_inputted 
        && input.size() == 0)
        return;

    std::stringstream ss {input};
    this->operation = operation;

    if (!is_first_num_inputted)
    {
        ss >> first_num;
        is_first_num_inputted = true;
        input.clear();
    } else  
        applyResult(ss);
}

void calc::CalculatorOperationContainer::applyResult(std::stringstream& ss)
{   
    double second_num {};
    ss >> second_num;

    double result = evaluate(first_num, second_num, operation);   
    reset();
    first_num = result;
    is_first_num_inputted = true;
}


//===============================================================
// namespace helper Function Definitions
//===============================================================

sf::Texture helpers::loadTextureFromFile(const std::string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

void addButtonFunction(
    Button& btn, 
    int value_index,
    calc::CalculatorOperationContainer& calc_data
)
{
    if (calc::button_values[value_index] == "del") 
        btn.setClickCallback([&calc_data](){ calc_data.backspace(); });

    else if (calc::button_values[value_index] == "=")
        btn.setClickCallback([&calc_data](){ calc_data.equal(); });

    else if (calc::button_values[value_index] == "+")
        btn.setClickCallback([&calc_data](){ calc_data.add(); });
    
    else if (calc::button_values[value_index] == "-")
        btn.setClickCallback([&calc_data](){ calc_data.subtract(); });

    else if (calc::button_values[value_index] == "*")
        btn.setClickCallback([&calc_data](){ calc_data.multiply(); });

    else if (calc::button_values[value_index] == "/")
        btn.setClickCallback([&calc_data](){ calc_data.divide(); });

    else 
    {   
        // This is guaranteed to be a digit character. can be period.
        char digit = std::string(calc::button_values[value_index])[0];
        btn.setClickCallback([&calc_data, digit](){ calc_data.add_digit(digit); });
    }
}

void helpers::prepareButtons(
    ButtonContainer& container, 
    calc::CalculatorOperationContainer& calc_data
)
{
        // Paths to the assets of these buttons
        static const std::vector<std::string> button_texture_paths = {
            // First row of button, btnclear counts as buttons in width
            "../assets/op-btns/btnclear.png",
            "../assets/op-btns/btndel.png",
            "../assets/op-btns/btnequal.png",
        
            // Second row of the buttons
            "../assets/num-btns/btn0.png",
            "../assets/num-btns/btn1.png",
            "../assets/num-btns/btn2.png",
            "../assets/op-btns/btnplus.png",
        
            // Third row of the buttons
            "../assets/num-btns/btn3.png",
            "../assets/num-btns/btn4.png",
            "../assets/num-btns/btn5.png",
            "../assets/op-btns/btndash.png",
        
            // Fourth row of the buttons
            "../assets/num-btns/btn6.png",
            "../assets/num-btns/btn7.png",
            "../assets/num-btns/btn8.png",
            "../assets/op-btns/btnaster.png",
        
            // Fifth row of the buttons
            "../assets/num-btns/btn9.png",
            "../assets/op-btns/btndot.png",
            "../assets/op-btns/btnempty.png",
            "../assets/op-btns/btnslash.png",
        }; 


    const sf::Vector2f STARTING_POINT = {17.0f, 266.0f};
    const int MARGIN_PX = 20;
    const int BUTTONS_PER_ROW = 4;

    float X {STARTING_POINT.x};
    float Y {STARTING_POINT.y};
    int BUTTON_COUNTER {};

    for (int i = 0; i < calc::button_texture_paths.size(); i++)
    {
        sf::Texture texture;
        texture.loadFromFile(calc::button_texture_paths[i]);
        
        // Clear button
        if (i == 0)
        {
            BUTTON_COUNTER += 2;
            Button clear_button { [&calc_data](){ calc_data.clear(); } };
            clear_button.setTexture(texture);
            clear_button.setPosition(STARTING_POINT);
            container.push_back(clear_button);
            continue;
        } else 
            BUTTON_COUNTER++;

        // Updating X and Y values
        if ((BUTTON_COUNTER - 1)% BUTTONS_PER_ROW == 0)
        {   
            // Get height of last element and add the gap or magin
            Y += (container.back().getTexture()->getSize().y) + MARGIN_PX;    
            X = STARTING_POINT.x;
        } 
        else 
        {
            X += (container.back().getTexture()->getSize().x) + MARGIN_PX;
        }

        // Add button functionality
        Button button;
        addButtonFunction(button, i, calc_data);
        button.setTexture(texture);
        button.setPosition({X, Y});
        container.push_back(button);
    }
}

sf::Color helpers::modifyColorByFactor(sf::Color color, float factor)
{
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
    return color;
}


