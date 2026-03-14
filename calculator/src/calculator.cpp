#include "data.h"
#include "mathlib/math.h"

int calculate(Data *data) {

  int error = 0;

  switch (data->op) {

  case '+':
    data->result = mathlib::AdditionOperation(data->num1, data->num2, &error);
    break;

  case '-':
    data->result =
        mathlib::SubtractionOperation(data->num1, data->num2, &error);
    break;

  case '*':
    data->result =
        mathlib::MultiplicationOperation(data->num1, data->num2, &error);
    break;

  case '/':
    data->result = mathlib::DivisionOperation(data->num1, data->num2, &error);
    break;

  case '^':
    data->result = mathlib::PowerOperation(data->num1, data->num2, &error);
    break;

  case '!':
    data->result = mathlib::FactorialOperation(data->num1, &error);
    break;
  }

  return error;
}
