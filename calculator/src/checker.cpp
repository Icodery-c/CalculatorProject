#include "checker.h"

int check(Data *data) {

  if ((data->op == '+') || (data->op == '-') || (data->op == '*') ||
      (data->op == '/') || (data->op == '^') || (data->op == '!')) {

    return 0;
  }

  return 1;
}
