#pragma once

#include <climits>

namespace mathlib {

  inline int AdditionOperation (int num1, int num2, int* error) {

    if ((num2 > 0 && num1 > INT_MAX - num2) || (num2 < 0 && num1 < INT_MIN - num2))
    {  *error = 1; return 0; }

    return num1 + num2;

  }

  inline int SubtractionOperation (int num1, int num2, int* error) {

    if ((num2 < 0 && num1 > INT_MAX + num2) || (num2 > 0 && num1 < INT_MIN + num2))
    { *error = 1; return 0; }

    return num1 - num2;

  }

  inline int MultiplicationOperation (int num1, int num2, int* error) {

    if (num1 != 0 && (num1 * num2) / num1 != num2)
    { *error = 1; return 0; }

    return num1 * num2;

  }

  inline int DivisionOperation (int num1, int num2, int* error) {

    if (num2 == 0) { *error = 1; return 0; }

    return num1 / num2;

  }

  inline int PowerOperation(int base, int exp, int* error) {

    int result = 1;

    for (int i = 0; i < exp; i++) {

      if (base != 0 && (result * base) / base != result)
      { *error = 1; return 0; }

      result *= base;

    }

    return result;

  }

  inline int FactorialOperation (int num, int* error) {

    if (num < 0) { *error = 1; return 0; }

    if (num <= 1) { return 1; }

    int result = FactorialOperation(num-1, error);

    if (*error) { return 0; }

    if (result > INT_MAX / num) { *error = 1; return 0;}

    return result * num;

  }

}
