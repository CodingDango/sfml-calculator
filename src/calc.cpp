#include "calc.hpp"

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