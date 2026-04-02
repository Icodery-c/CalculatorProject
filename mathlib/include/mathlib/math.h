#pragma once

#include <climits>

namespace mathlib {

  inline int AdditionOperation(int num1, int num2, int* error) {

    int result;

    if (__builtin_add_overflow(num1, num2, &result))
    {
        *error = 1;
        return 0;
    }

    return result;

  }

  inline int SubtractionOperation(int num1, int num2, int* error) {

    int result;

    if (__builtin_sub_overflow(num1, num2, &result))
    {
        *error = 1;
        return 0;
    }

    return result;

  }

  inline int MultiplicationOperation(int num1, int num2, int* error) {

    int result;

    if (__builtin_mul_overflow(num1, num2, &result))
    {
        *error = 1;
        return 0;
    }

    return result;

  }

  inline int DivisionOperation (int num1, int num2, int* error) {

    if (num2 == 0) { *error = 1; return 0; }

    return num1 / num2;

  }

  inline int PowerOperation(int base, int exp, int* error) {

      int result = 1;

      for (int i = 0; i < exp; i++)
      {
          if (__builtin_mul_overflow(result, base, &result))
          {
              *error = 1;
              return 0;
          }
      }

      return result;
  }

  inline int FactorialOperation(int num, int* error) {

      if (num < 0) {

          *error = 1;
          return 0;
      }

      if (num <= 1)
          return 1;

      int prev = FactorialOperation(num - 1, error);

      if (*error)
          return 0;

      int result = 0;

      if (__builtin_mul_overflow(prev, num, &result)) {

          *error = 1;
          return 0;
      }

      return result;
  }

}
