#pragma once

#include "data.h"

class Parser {

public:
    Parser() = default;
    ~Parser() = default;

    Parser(const Parser&) = default;
    Parser& operator=(const Parser&) = default;

    Parser(Parser&&) = default;
    Parser& operator=(Parser&&) = default;

    Data parse(int argc, char** argv);
};