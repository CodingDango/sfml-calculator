#ifndef CALC_HPP
#define CALC_HPP

#include <sstream>
#include <string>
#include <iomanip>  // Precision.

namespace calc 
{   
    class CalculatorOperationContainer
    {   
    public:
        CalculatorOperationContainer();

        std::string input;
        std::string result_string;

        long double result;
        char operation;
        bool is_operation_inputted;

        void add_digit(char digit);
        void reset();
        void backspace();
        void clear();
        void add();
        void subtract();
        void equal();
        void multiply();
        void divide();

    private:
        double evaluate(double a, double b, char operation) const;
        void doOperatorOperation(char operation);
        void applyResult();
        void updateResultString();
    }; 
}

#endif