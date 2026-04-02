#include "checker.h"
#include <stdexcept>
#include <string>

void Checker::check(const Data& data) {

    if (data.op == Operation::Help) {
        return;
    }

    if (data.op != Operation::Add      &&
        data.op != Operation::Subtract &&
        data.op != Operation::Multiply &&
        data.op != Operation::Divide   &&
        data.op != Operation::Power    &&
        data.op != Operation::Factorial) {

        throw std::runtime_error("Unknown operation");
    }
}