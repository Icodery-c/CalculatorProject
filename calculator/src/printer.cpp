#include "printer.h"

#include <iostream>

void Printer::printResult(int result) { std::cout << "Result = " << result << std::endl; }

void Printer::printError(const std::string& msg) {std::cout << "Error: " << msg << std::endl; }

void Printer::printHelp()
{
    std::cout
        << "Usage: calculator '<json>'\n"
        << "\n"
        << "JSON format:\n"
        << "  {\"num1\": <int>, \"num2\": <int>, \"op\": \"<operator>\"}\n"
        << "  {\"num1\": <int>, \"op\": \"!\"}  (factorial, num2 not required)\n"
        << "\n"
        << "Supported operators:\n"
        << "  +   addition        {\"num1\": 5, \"num2\": 3, \"op\": \"+\"}  ->  8\n"
        << "  -   subtraction     {\"num1\": 5, \"num2\": 3, \"op\": \"-\"}  ->  2\n"
        << "  *   multiplication  {\"num1\": 5, \"num2\": 3, \"op\": \"*\"}  ->  15\n"
        << "  /   division        {\"num1\": 6, \"num2\": 3, \"op\": \"/\"}  ->  2\n"
        << "  ^   power           {\"num1\": 2, \"num2\": 8, \"op\": \"^\"}  ->  256\n"
        << "  !   factorial       {\"num1\": 5, \"op\": \"!\"}               ->  120\n"
        << "\n"
        << "Notes:\n"
        << "  - num2 is not required for factorial (!)\n"
        << "  - division by zero is not allowed\n"
        << "  - overflow is detected for all operations\n"
        << std::endl;
}