#pragma once

enum class Operation {
    
    Add,
    Subtract,
    Multiply,
    Divide,
    Power,
    Factorial,
    Help

};

struct Data {

    int num1;
    int num2;
    Operation op;
    int result;

};