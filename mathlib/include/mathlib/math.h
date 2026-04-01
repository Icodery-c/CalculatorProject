#pragma once

#include <climits>
#include <stdexcept>

namespace mathlib {

  inline int AdditionOperation(int num1, int num2) {

    int result;

    if (__builtin_add_overflow(num1, num2, &result))
    {
        throw std::overflow_error("Addition overflow");

    }

    return result;

  }

  inline int SubtractionOperation(int num1, int num2) {

    int result;

    if (__builtin_sub_overflow(num1, num2, &result))
    {
        throw std::overflow_error("Subtraction overflow");

    }

    return result;

  }

  inline int MultiplicationOperation(int num1, int num2) {

    int result;

    if (__builtin_mul_overflow(num1, num2, &result))
    {
        throw std::overflow_error("Multiplication overflow");

    }

    return result;

  }

  inline int DivisionOperation (int num1, int num2) {

    if (num2 == 0) { throw std::runtime_error("Division by zero"); }

    return num1 / num2;

  }

  inline int PowerOperation(int base, int exp) {

      int result = 1;

      for (int i = 0; i < exp; i++)
      {
          if (__builtin_mul_overflow(result, base, &result))
          {
                throw std::overflow_error("Power overflow");
          }
      }

      return result;
  }

  inline int FactorialOperation(int num) {

    if (num < 0) { throw std::runtime_error("Negative factorial"); }

    if (num <= 1) { return 1; }

    int prev = FactorialOperation(num - 1); 

    int result = 0;
    
    if (__builtin_mul_overflow(prev, num, &result)) { throw std::overflow_error("Factorial overflow"); }

    return result;
}

}
