#include "checker.h"
#include <stdexcept>
#include <string>

void Checker::check(const Data& data) {

    if (!((data.op == '+') || (data.op == '-') || (data.op == '*') ||
      (data.op == '/') || (data.op == '^') || (data.op == '!'))) {

        throw std::runtime_error("Unknown operation");

    }

}