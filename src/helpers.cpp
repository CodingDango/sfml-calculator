#include "headers/helpers.hpp"

//===============================================================
// namespace utils function definitions
//===============================================================

sf::Texture utils::loadTexture(const std::string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

sf::Color utils::modifyColorByFactor(sf::Color color, float factor)
{
    color.r *= factor;
    color.g *= factor;
    color.b *= factor;
    return color;
}

sf::Font utils::loadFont(const std::string& path)
{
    sf::Font font {};
    if (!font.loadFromFile(path))
        std::cerr << "Font with path '" << path << "' could not be loaded.\n";
    return font;
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
    result = 0;
    operation = '~';
    is_operation_inputted = false;
}

void calc::CalculatorOperationContainer::backspace()
{
    if (input.size() != 0)
        input.pop_back();
    else 
    {
        is_operation_inputted = false;
        operation = '~';
    }
}

void calc::CalculatorOperationContainer::clear()
{
    reset();
}

void calc::CalculatorOperationContainer::equal()
{   
    if (!is_operation_inputted || input.size() == 0) 
        return;

    std::stringstream ss {input};   // ss contains the second number
    applyResult(ss);  
    
    // After using equals, reset the operations.
    is_operation_inputted = false;
    operation = false;                   
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
            return a;   // return number unmodified
        }
        return a / b;

    default:
        return 0;
    }
}

void calc::CalculatorOperationContainer::doOperatorOperation(char operation)
{   
    this->operation = operation;
    is_operation_inputted = true;

    if (input.size() == 0)
        return;

    std::stringstream ss {input};
    applyResult(ss);
}

void calc::CalculatorOperationContainer::applyResult(std::stringstream& ss)
{   
    double input_num {};
    ss >> input_num;
    result = evaluate(result, input_num, operation);     
    input.clear();
}


//===============================================================
// namespace assets Definitions
//===============================================================

const std::vector<assets::ButtonInitializerData> assets::button_initializers = {

    // First row
    ButtonInitializerData("clear", utils::loadTexture("../assets/op-btns/oper-clear.png")),
    ButtonInitializerData("del", utils::loadTexture("../assets/op-btns/oper-del.png")),
    ButtonInitializerData("/", utils::loadTexture("../assets/op-btns/oper-divide.png")),
        
    // Second row
    ButtonInitializerData("7", utils::loadTexture("../assets/num-btns/num-7.png")),
    ButtonInitializerData("8", utils::loadTexture("../assets/num-btns/num-8.png")),
    ButtonInitializerData("9", utils::loadTexture("../assets/num-btns/num-9.png")), 
    ButtonInitializerData("*", utils::loadTexture("../assets/op-btns/oper-multiply.png")),

    // Third row
    ButtonInitializerData("4", utils::loadTexture("../assets/num-btns/num-4.png")),
    ButtonInitializerData("5", utils::loadTexture("../assets/num-btns/num-5.png")),
    ButtonInitializerData("6", utils::loadTexture("../assets/num-btns/num-6.png")),
    ButtonInitializerData("-", utils::loadTexture("../assets/op-btns/oper-subtract.png")),

    // Fourth row
    ButtonInitializerData("1", utils::loadTexture("../assets/num-btns/num-1.png")),
    ButtonInitializerData("2", utils::loadTexture("../assets/num-btns/num-2.png")),
    ButtonInitializerData("3", utils::loadTexture("../assets/num-btns/num-3.png")),
    ButtonInitializerData("+", utils::loadTexture("../assets/op-btns/oper-add.png")),

    // Fifth row
    ButtonInitializerData("empty", utils::loadTexture("../assets/num-btns/num-empty.png")),
    ButtonInitializerData("0", utils::loadTexture("../assets/num-btns/num-0.png")),
    ButtonInitializerData(".", utils::loadTexture("../assets/num-btns/char-dot.png")),
    ButtonInitializerData("=", utils::loadTexture("../assets/op-btns/oper-equals.png")),
}; 

const sf::Font assets::my_font { 
    utils::loadFont("../assets/fonts/YuGothM.ttc")
};


//===============================================================
// namespace core Function Definitions
//===============================================================

void core::prepareButtons(
    ButtonContainer& container, 
    calc::CalculatorOperationContainer& calc_data
)
{
    const sf::Vector2f STARTING_POINT = {19.60f, 200.0f};
    const int MARGIN_X_PX = 27;
    const int MARGIN_Y_PX = 20;
    const int BUTTONS_PER_ROW = 4;

    float X {STARTING_POINT.x};
    float Y {STARTING_POINT.y};
    int BUTTON_COUNTER {};

    for (int i = 0; i < assets::button_initializers.size(); i++)
    {   
        const auto& btn_initializer = assets::button_initializers[i];

        // Clear button
        if (i == 0)
        {
            BUTTON_COUNTER += 2;
            Button clear_button { [&calc_data](){ calc_data.clear(); } };
            clear_button.setTexture(btn_initializer.texture);
            clear_button.setPosition(STARTING_POINT);
            container.push_back(clear_button);
            continue;
        } else 
            BUTTON_COUNTER++;

        // Updating X and Y values
        if ((BUTTON_COUNTER - 1)% BUTTONS_PER_ROW == 0)
        {   
            // Get height of last element and add the gap or magin
            Y += (container.back().getTexture()->getSize().y) + MARGIN_Y_PX;    
            X = STARTING_POINT.x;
        } 
        else 
        {
            X += (container.back().getTexture()->getSize().x) + MARGIN_X_PX;
        }

        // Add button functionality
        Button button;
        addButtonFunction(button, btn_initializer, calc_data);
        button.setTexture(btn_initializer.texture);
        button.setPosition({X, Y});
        container.push_back(button);
    }
}

void core::addButtonFunction(
    Button& btn, 
    const assets::ButtonInitializerData& initializer,
    calc::CalculatorOperationContainer& calc_data
)
{   
    const std::string btn_value = initializer.value;

    if (btn_value == "del") 
        btn.setClickCallback([&calc_data](){ calc_data.backspace(); });

    else if (btn_value == "=")
        btn.setClickCallback([&calc_data](){ calc_data.equal(); });

    else if (btn_value == "+")
        btn.setClickCallback([&calc_data](){ calc_data.add(); });
    
    else if (btn_value == "-")
        btn.setClickCallback([&calc_data](){ calc_data.subtract(); });

    else if (btn_value == "*")
        btn.setClickCallback([&calc_data](){ calc_data.multiply(); });

    else if (btn_value == "/")
        btn.setClickCallback([&calc_data](){ calc_data.divide(); });

    else 
    {   
        // This is guaranteed to be a digit character. can be period.
        char digit = btn_value[0];
        btn.setClickCallback([&calc_data, digit](){ calc_data.add_digit(digit); });
    }
}
