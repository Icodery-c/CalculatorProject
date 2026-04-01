#include "calculator.h"
#include "mathlib/math.h"

#include <stdexcept>

int Calculator::calculate(Data& data) {

    switch (data.op)
    {

        case '+':
            data.result = mathlib::AdditionOperation(data.num1, data.num2);
            break;

        case '-':
            data.result = mathlib::SubtractionOperation(data.num1, data.num2);
            break;
    
        case '*':
            data.result = mathlib::MultiplicationOperation(data.num1, data.num2);
            break;
    
        case '/':
            data.result = mathlib::DivisionOperation(data.num1, data.num2);
            break;
        
        case '^':
            data.result = mathlib::PowerOperation(data.num1, data.num2);
            break;

        case '!':
            data.result = mathlib::FactorialOperation(data.num1);
            break;

        default:
            //Если каким то чудом checker не сработает(но этого не должно быть), просто на всякий случай
            throw std::logic_error("Calculator: Unknown operation (checker failed)");
    }

    return data.result;

}


