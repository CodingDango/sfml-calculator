#include "headers/helpers.hpp"

//===============================================================
// namespace helpers function definitions
//===============================================================

sf::Texture helpers::loadTextureFromFile(const std::string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

sf::Color helpers::modifyColorByFactor(sf::Color color, float factor)
{
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
    return color;
}


//===============================================================
// Class CalculatorOperationContainer Public Methods Definitions
//===============================================================

void calc::CalculatorOperationContainer::add_digit(char digit)
{   
    // Checks if period is already input, to avoid multiple periods.
    if (digit == '.' && input.find_first_of(digit) != std::string::npos)
        return;
    input += digit;
}

void calc::CalculatorOperationContainer::reset()
{   
    input.clear();
    first_num = double();
    operation = char();
    is_first_num_inputted = false;
    is_operation_inputted = false;
}

void calc::CalculatorOperationContainer::backspace()
{
    if (input.size() != 0)
        input.pop_back();
}

void calc::CalculatorOperationContainer::clear()
{
    reset();
}

void calc::CalculatorOperationContainer::equal()
{
    if (!is_operation_inputted 
        || (!is_first_num_inputted
        && input.size() == 0))
        return;
    
    std::stringstream ss {input};   // ss contains the second number
    applyResult(ss);                       
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
        // Handle division by 0
        if (b == 0) {
            return 0;
        }
        return a / b;

    default:
        return a; // return the same unmodified number. b is 0 if operation hasnt been selected
    }
}

void calc::CalculatorOperationContainer::doOperatorOperation(char operation)
{   
    this->operation = operation;
    is_operation_inputted = true;

    if (input.size() == 0)
        return;

    std::stringstream ss {input};

    if (!is_first_num_inputted)
    {
        ss >> first_num;
        is_first_num_inputted = true;
        input.clear();
    } else  
        applyResult(ss);
    this->operation = operation;
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
// namespace core Function Definitions
//===============================================================

void core::prepareButtons(
    ButtonContainer& container, 
    calc::CalculatorOperationContainer& calc_data
)
{
    const sf::Vector2f STARTING_POINT = {17.0f, 266.0f};
    const int MARGIN_PX = 20;
    const int BUTTONS_PER_ROW = 4;

    float X {STARTING_POINT.x};
    float Y {STARTING_POINT.y};
    int BUTTON_COUNTER {};

    for (int i = 0; i < calc::button_texture_paths.size(); i++)
    {
        // Clear button
        if (i == 0)
        {
            BUTTON_COUNTER += 2;
            Button clear_button { [&calc_data](){ calc_data.clear(); } };
            clear_button.setTexture(calc::button_texture_paths[i]);
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
        button.setTexture(calc::button_texture_paths[i]);
        button.setPosition({X, Y});
        container.push_back(button);
    }
}

void core::addButtonFunction(
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
