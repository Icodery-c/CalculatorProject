#pragma once

#include "data.h"

class Calculator {

public:
    Calculator() = default;
    ~Calculator() = default;

    Calculator(const Calculator&) = default;
    Calculator& operator=(const Calculator&) = default;

    Calculator(Calculator&&) = default;
    Calculator& operator=(Calculator&&) = default;

    int calculate(Data& data);
};