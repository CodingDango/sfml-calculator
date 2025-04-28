#ifndef CALC_HPP
#define CALC_HPP

#include <sstream>
#include <string>

namespace calc 
{   
    class CalculatorOperationContainer
    {   
    public:
        std::string input {};
        double result {};
        char operation {};
        bool is_operation_inputted = false;

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
        void applyResult(std::stringstream& ss);
    }; 
}

#endif