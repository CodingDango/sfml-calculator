#include "calc.hpp"
#include <iostream>

//===============================================================
// Class CalculatorOperationContainer Public Methods Definitions
//===============================================================

calc::CalculatorOperationContainer::CalculatorOperationContainer()
{
    reset();
}

void calc::CalculatorOperationContainer::add_digit(char digit)
{   
    // Checks if period is already input, to avoid multiple periods.
    if (digit == '.' && input.find_first_of(digit) != std::string::npos)
        return;
    input += digit;
}

void calc::CalculatorOperationContainer::reset()
{   
    result = 0;
    updateResultString();           // updates_result string
    is_operation_inputted = false;
    input.clear();
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

    applyResult();  
    
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
          return b;   // return number unmodified
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

  applyResult();
}

void calc::CalculatorOperationContainer::applyResult()
{   
    std::stringstream ss {input};
    double input_num {};
    ss >> input_num;                            // From string result

    result = evaluate(result, input_num, operation);  
    updateResultString();

    input.clear();
}

void calc::CalculatorOperationContainer::updateResultString()
{
    std::stringstream ss {}; 
    ss << std::fixed << std::setprecision(5);   // Show 5 digits after decimal point.
    ss << result;                               // Result is the number
    result_string = ss.str();
}